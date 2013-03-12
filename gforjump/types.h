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
	UBYTE x, y;            /* position on layer in blocks */
	UBYTE data_index;      /* index of data in the data array */
	UBYTE sub_x, sub_y;    /* position inside the block (8th pixels) */
	BYTE speed_x, speed_y; /* speeds (8th pixels / frame, -128..127)  */
	UBYTE state;
} game_object;
