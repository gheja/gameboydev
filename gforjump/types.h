/* gforjump for Game Boy - https://github.com/gheja/gameboydev/ */

// structure definitions
typedef struct _game_tile
{
	UBYTE x, y;          /* position on layer in blocks */
	UBYTE data_index;    /* index of data in the data array */
	UBYTE width, height; /* count of the elements */
} game_tile;

typedef struct _game_object
{
	INT16 x, y;             /* position on layer in blocks */
	UBYTE data_index;       /* index of data in the data array */
	INT16 speed_x, speed_y; /* speeds (8th pixels / frame)  */
	UBYTE state;
} game_object;

typedef struct _level
{
	INT16 scroll_x;
	INT16 scroll_y;
	INT16 scroll_x_min, scroll_x_max;
	INT16 scroll_y_min, scroll_y_max;
	game_tile tiles[255];
	game_object objects[255];
} level;
