/* gforjump for Game Boy - https://github.com/gheja/gameboydev/ */

game_tile level1_tiles[] = {
	/* x, y, index, width, height */
	{  0, 17, 1, 6, 1 },
	{  2, 13, 1, 1, 1 },
	{  2, 14, 1, 6, 1 },
	{ 10, 15, 1, 3, 1 },
	{ 14, 11, 1, 3, 1 },
	{ 18, 18, 1, 5, 1 },
	{ 18, 17, 3, 1, 1 },
	
	{ 0, 0, 0, 0, 0 }
};

game_object level1_objects[] = {
	/* x, y, index, speed_x, speed_y, state */
	{ 256, 128, 1, 0, 0, SPRITE_STATE_FALLING }, /* player */
	
	{ 0, 0, 0, 0, 0, 0 }
};
