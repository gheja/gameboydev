/* gforjump for Game Boy - https://github.com/gheja/gameboydev/ */

/* level data */
const game_tile tiles[] = {
	{  0, 17, 1, 6, 1 },
	{  2, 13, 1, 1, 1 },
	{  2, 14, 1, 6, 1 },
	{ 10, 15, 1, 3, 1 },
	{ 14, 11, 1, 3, 1 },
	{ 18, 18, 1, 5, 1 },
	{ 18, 17, 3, 1, 1 },

	{ 0, 0, 0, 0, 0 }
};

game_object objects[] = {
	{ 2, 2, 1, 0, 0, 0, 0, 0 }, /* player */

	{ 0, 0, 0, 0, 0, 0, 0, 0 }
};
