// Brian Chrzanowski
// 2022-04-24 04:48:54
//
// A Dungeon Generator.
//
// Dungeon Ideas:
//
// For her wedding, the bride gets:
//     something old, something new, something borrowed, and something blue.
//
// Old      - What was the dungeon for?
// New      - What is happening now?
// Borrowed - Monsters, Characters, Treasure, Tropes, etc.
// Blue     - Sad / Emotional Content. Make the players feel something for the space(?)
//
// 5 Room Dungeon Technique
//
// 1. Entrance Guardian
// 2. Puzzle or Role Playing
// 3. Setback or Twist
// 4. Boss Fight
// 5. Reward
//
// Additional Techniques
//
// 1. Secret Entrance (or Two)
// 2. Secret Exit
// 3. Secret Preview
//
// Considerations
//
// Clearly, we'll be printing the maps themselves as ASCII (for now) grids; however, we'll also
// print out a textual description of every single room, Dwarf Fortress style.
//
// An interesting thought is to output this into/onto something that can be easily printed at like,
// a FedEx or something. Maybe, print a giant wax paper thing underneath, then 
//
// As we might want to print the map out at a FedEx or something, it'd be a good idea to be able
// to save the map, or read it back in from stdin or something, such that we can reload the world,
// and possibly re-generate the goodies and monsters. We can print off the map without the goodies,
// then we can re-use it multiple times.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "generated.h"

#define COLOR_FG_BLACK   (30)
#define COLOR_FG_RED     (31)
#define COLOR_FG_GREEN   (32)
#define COLOR_FG_YELLOW  (33)
#define COLOR_FG_BLUE    (34)
#define COLOR_FG_MAGENTA (35)
#define COLOR_FG_CYAN    (36)
#define COLOR_FG_WHITE   (37)

#define COLOR_BG_BLACK   (40)
#define COLOR_BG_RED     (41)
#define COLOR_BG_GREEN   (42)
#define COLOR_BG_YELLOW  (43)
#define COLOR_BG_BLUE    (44)
#define COLOR_BG_MAGENTA (45)
#define COLOR_BG_CYAN    (46)
#define COLOR_BG_WHITE   (47)

#define ESC_RESET        (0)
#define ESC_BOLD         (1)
#define ESC_UNDERLINE    (4)

#define TILE_FLOOR       ('.')
#define TILE_WALL_N      ('-')
#define TILE_WALL_E      ('|')
#define TILE_WALL_S      ('_')
#define TILE_WALL_W      ('|')

typedef struct tile {
	int c;
	int fg;
	int bg;

	// tile properties go here
} tile;

typedef struct map {
	tile *tiles;
	int w, h;
} map;

typedef struct dungeon {
} dungeon;

// MapAllocate: allocates a map with dimensionality W x H
map *MapAllocate(int w, int h)
{
	map *m = calloc(1, sizeof(*m));

	if (!m) {
		return NULL;
	}

	m->w = w;
	m->h = h;

	m->tiles = calloc(w * h, sizeof(*m->tiles));

	return m;
}

// MapGenerate: generates a map, given the parameters
map *MapGenerate(int w, int h)
{
	map *m = MapAllocate(w, h);
	if (m == NULL)
		return NULL;

	memset(m->tiles, 'x', sizeof(*m->tiles) * m->w * m->h);

	for (int i = 0; i < m->w * m->h; i++) {
		m->tiles[i].c  = 'c';
		m->tiles[i].fg = COLOR_FG_RED;
		m->tiles[i].bg = COLOR_BG_MAGENTA;
	}

	return m;
}

// MapPrint: dumps a map to stdout
void MapPrint(map *m)
{
	for (int i = 0; i < m->h; i++) {
		for (int j = 0; j < m->w; j++) {
			printf("\033[1;%dm", m->tiles[j + i * m->w].fg);
			printf("\033[1;%dm", m->tiles[j + i * m->w].bg);
			putchar(m->tiles[j + i * m->w].c);
			printf("\033[0m");
		}
		putchar('\n');
	}
}

// MapFree: frees the map
void MapFree(map *m)
{
	free(m->tiles);
	free(m);
}

int main(int argc, char **argv)
{
	map *themap = MapGenerate(30, 16);
	MapPrint(themap);
	MapFree(themap);
	return 0;
}
