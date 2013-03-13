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
