/* gforjump for Game Boy - https://github.com/gheja/gameboydev/ */

#include <gb/gb.h>
#include <string.h>
#include "types.h"
#include "consts.h"
#include "gfx_gbc.c"
#include "level1.c"

level _level;

void init_background()
{
	set_bkg_data(BACKGROUND_TILE_START, BACKGROUND_TILE_COUNT, BACKGROUND_TILE_DATA);
}

void init_sprites()
{
	set_sprite_data(SPRITE_TILE_START, SPRITE_TILE_COUNT, SPRITE_TILE_DATA);
	set_sprite_tile(0, 0);
	set_sprite_prop(0, 0);
	move_sprite(0, 20, 20);
	_level.objects[0].state = SPRITE_STATE_FALLING;
}

void load_level(UBYTE level_id)
{
	/* TODO: level_id is currently ignored */
	
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
	
	for (i=0; level1_tiles[i].data_index != 0; i++)
	{
		memcpy(&_level.tiles[i], &level1_tiles[i], sizeof(game_tile));
	}
	// terminator
	_level.tiles[i].data_index = 0;
	
	for (i=0; level1_objects[i].data_index != 0; i++)
	{
		memcpy(&_level.objects[i], &level1_objects[i], sizeof(game_object));
	}
	// terminator
	_level.objects[i].data_index = 0;
	
	/* TODO: destroy the objects */
	
	for (i=0; _level.tiles[i].data_index != 0; i++)
	{
		bkg_tiles[0] = _level.tiles[i].data_index;
		for (j=0; j<_level.tiles[i].width; j++)
		{
			for (k=0; k<_level.tiles[i].height; k++)
			{
				set_bkg_tiles(_level.tiles[i].x + j, _level.tiles[i].y + k, 1, 1, bkg_tiles);
			}
		}
	}
}

void move_object(UBYTE object_id, INT16 x, INT16 y)
{
	_level.objects[object_id].x = x;
	_level.objects[object_id].y = y;
	
	/* object update should be separated from tile/sprite update */
	move_sprite(object_id, _level.objects[object_id].x / 8, _level.objects[object_id].y / 8);
}

void scroll_object(UBYTE object_id, INT16 x, INT16 y)
{
	_level.objects[object_id].x += x;
	_level.objects[object_id].y += y;
	
	/* object update should be separated from tile/sprite update */
	move_sprite(object_id, _level.objects[object_id].x / 8, _level.objects[object_id].y / 8);
}

UBYTE _keys;

void process_keys()
{
	UBYTE is_running;
	
	_keys = joypad();
	
	is_running = _keys & J_A;
	
	if(_keys & J_UP)
	{
		if (_level.objects[0].state != SPRITE_STATE_JUMPING && _level.objects[0].state != SPRITE_STATE_FALLING)
		{
			_level.objects[0].state = SPRITE_STATE_JUMPING;
			_level.objects[0].speed_y = -24;
		}
	}
	
	if(_keys & J_DOWN)
	{
		// posy++;
	}
	
	if(_keys & J_LEFT)
	{
		if (_level.objects[0].state == SPRITE_STATE_STANDING)
		{
			_level.objects[0].state = SPRITE_STATE_WALKING;
		}
		
		if (is_running)
		{
			if (_level.objects[0].speed_x > -24)
			{
				_level.objects[0].speed_x -= 1;
			}
		}
		else
		{
			if (_level.objects[0].speed_x > -12)
			{
				_level.objects[0].speed_x -= 1;
			}
			else
			{
				_level.objects[0].speed_x += 1;
			}
		}
	}
	
	if(_keys & J_RIGHT)
	{
		if (_level.objects[0].state == SPRITE_STATE_STANDING)
		{
			_level.objects[0].state = SPRITE_STATE_WALKING;
		}
		
		if (is_running)
		{
			if (_level.objects[0].speed_x < 24)
			{
				_level.objects[0].speed_x += 1;
			}
		}
		else
		{
			if (_level.objects[0].speed_x < 12)
			{
				_level.objects[0].speed_x += 1;
			}
			else
			{
				_level.objects[0].speed_x -= 1;
			}
		}
	}
}

void update_player()
{
	// slow down
	if (!_keys & (J_RIGHT || J_LEFT))
	{
		if (_level.objects[0].speed_x < -1)
		{
			_level.objects[0].speed_x += 1;
		}
		else if (_level.objects[0].speed_x > 1)
		{
			_level.objects[0].speed_x -= 1;
		}
		else if (_level.objects[0].speed_x != 0)
		{
			_level.objects[0].speed_x = 0;
			_level.objects[0].state = SPRITE_STATE_STANDING;
		}
	}
	
	//gravity
	if (_level.objects[0].speed_y < 64)
	{
		_level.objects[0].speed_y++;
	}
	
	switch (_level.objects[0].state)
	{
		case 3: // SPRITE_STATE_JUMPING
			
			if (_level.objects[0].speed_y > 0)
			{
				_level.objects[0].state = SPRITE_STATE_FALLING;
			}
		break;
		
	}
}

void collision_check()
{
	UBYTE wanted_x;
	UBYTE wanted_y;
	
	/* collision check */
	if (_level.objects[0].speed_y > 0) // below player
	{
		if (_level.objects[0].y > 12 * 8 * 8)
		{
			_level.objects[0].speed_y = 0;
			if (_level.objects[0].speed_x != 0)
			{
				_level.objects[0].state = SPRITE_STATE_WALKING;
			}
		}
	}
	else if (_level.objects[0].speed_y < 0) // above player
	{
	}
	
	if (_level.objects[0].speed_x > 0) // right of player
	{
	}
	else if (_level.objects[0].speed_x < 0) // left of player
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
	scroll_object(0, _level.objects[0].speed_x, _level.objects[0].speed_y);
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
	
	load_level(1);
	
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
