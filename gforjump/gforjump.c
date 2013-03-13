/* gforjump for Game Boy - https://github.com/gheja/gameboydev/ */

#include <gb/gb.h>
#include "types.h"
#include "consts.h"
#include "tiles_gbc.c"
#include "level1.c"

void init_background()
{
	set_bkg_data(0x00, 2, bkg_data);
}

void init_sprites()
{
	set_sprite_data(0x00, 1, sprite_data);
	set_sprite_tile(0, 0);
	set_sprite_prop(0, 0);
	move_sprite(0, 20, 20);
	objects[0].state = SPRITE_STATE_FALLING;
}

void load_level()
{
	UBYTE i, j, k;
	unsigned char bkg_tiles[1];
	
	/* clear the background */
	bkg_tiles[0] = 0;
	for (i=0; i<40; i++)
	{
		for (j=0; j<40; j++)
		{
			set_bkg_tiles(i, j, 1, 1, bkg_tiles);
		}
	}
	
	for (i=0; tiles[i].data_index != 0; i++)
	{
		bkg_tiles[0] = tiles[i].data_index;
		for (j=0; j<tiles[i].width; j++)
		{
			for (k=0; k<tiles[i].height; k++)
			{
				set_bkg_tiles(tiles[i].x + j, tiles[i].y + k, 1, 1, bkg_tiles);
			}
		}
	}
	
}

void move_object(UBYTE object_id, INT16 x, INT16 y)
{
	objects[object_id].x = x;
	objects[object_id].y = y;
	
	/* object update should be separated from tile/sprite update */
	move_sprite(object_id, objects[object_id].x / 8, objects[object_id].y / 8);
}

void scroll_object(UBYTE object_id, INT16 x, INT16 y)
{
	objects[object_id].x += x;
	objects[object_id].y += y;
	
	/* object update should be separated from tile/sprite update */
	move_sprite(object_id, objects[object_id].x / 8, objects[object_id].y / 8);
}

UBYTE _keys;

void process_keys()
{
	UBYTE is_running;
	
	_keys = joypad();
	
	is_running = _keys & J_A;
	
	if(_keys & J_UP)
	{
		if (objects[0].state != SPRITE_STATE_JUMPING)
		{
			objects[0].state = SPRITE_STATE_JUMPING;
			objects[0].speed_y = -24;
		}
	}
	
	if(_keys & J_DOWN)
	{
		// posy++;
	}
	
	if(_keys & J_LEFT)
	{
		if (objects[0].state == SPRITE_STATE_STANDING)
		{
			objects[0].state = SPRITE_STATE_WALKING;
		}
		
		if (is_running)
		{
			if (objects[0].speed_x > -24)
			{
				objects[0].speed_x -= 1;
			}
		}
		else
		{
			if (objects[0].speed_x > -12)
			{
				objects[0].speed_x -= 1;
			}
			else
			{
				objects[0].speed_x += 1;
			}
		}
	}
	
	if(_keys & J_RIGHT)
	{
		if (objects[0].state == SPRITE_STATE_STANDING)
		{
			objects[0].state = SPRITE_STATE_WALKING;
		}
		
		if (is_running)
		{
			if (objects[0].speed_x < 24)
			{
				objects[0].speed_x += 1;
			}
		}
		else
		{
			if (objects[0].speed_x < 12)
			{
				objects[0].speed_x += 1;
			}
			else
			{
				objects[0].speed_x -= 1;
			}
		}
	}
}

void update_player()
{
	// slow down
	if (!_keys & (J_RIGHT || J_LEFT))
	{
		if (objects[0].speed_x < -1)
		{
			objects[0].speed_x += 1;
		}
		else if (objects[0].speed_x > 1)
		{
			objects[0].speed_x -= 1;
		}
		else if (objects[0].speed_x != 0)
		{
			objects[0].speed_x = 0;
			objects[0].state = SPRITE_STATE_STANDING;
		}
	}
	
	//gravity
	if (objects[0].speed_y < 64)
	{
		objects[0].speed_y++;
	}
	
	switch (objects[0].state)
	{
		case 3: // SPRITE_STATE_JUMPING
			
			if (objects[0].speed_y > 0)
			{
				objects[0].state = SPRITE_STATE_FALLING;
			}
		break;
		
	}
}

void collision_check()
{
	UBYTE wanted_x;
	UBYTE wanted_y;
	
	/* collision check */
	if (objects[0].speed_y > 0) // below player
	{
		if (objects[0].y > 12 * 8 * 8)
		{
			objects[0].speed_y = 0;
			if (objects[0].speed_x != 0)
			{
				objects[0].state = SPRITE_STATE_WALKING;
			}
		}
	}
	else if (objects[0].speed_y < 0) // above player
	{
	}
	
	if (objects[0].speed_x > 0) // right of player
	{
	}
	else if (objects[0].speed_x < 0) // left of player
	{
	}
}

void animate_background()
{
}

void animate_sprites()
{
}

void update_background()
{
}

void update_sprites()
{
	scroll_object(0, objects[0].speed_x, objects[0].speed_y);
}

int main()
{
	UBYTE x = 0;
	unsigned char bkg_tiles[1];
	
	// disable interrupts for the time of init
	disable_interrupts();
	
	// turn the display off for the time of init
	DISPLAY_OFF;
	
	// set the background data
	init_background();
	init_sprites();
	
	load_level();
	
	// make background layer visible
	SHOW_BKG;
	SHOW_SPRITES;
	
	// reenable interrupts
	enable_interrupts();
	
	// turn the display back on
	DISPLAY_ON;
	
	/* Set palettes */
	BGP_REG = OBP0_REG = OBP1_REG = 0xE4U;
	
	// super meat boy 36x20 tiles
	// gforjump 160x120 px, 8x8 px/tile = 20x15 tiles
	// gameboy 160x144 px, 8x8 px/tile = 20x18 tiles
	
	while(1)
	{
		wait_vbl_done();
		
		x++;
		
		bkg_tiles[0] = (x / 16) % 2;
		set_bkg_tiles(1, 1, 1, 1, bkg_tiles);
		
		process_keys();
		
		animate_background();
		animate_sprites();
		
		update_player();
		collision_check();
		update_background();
		update_sprites();
	}
	
	return 0;
}
