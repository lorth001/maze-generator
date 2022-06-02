#ifndef MAZE_H
#define MAZE_H

#include "image.h"

typedef struct {
	pixel_t *pixels;
	int width;
	int height;
	int line_weight;
} cell_t;

bitmap_t *init_maze(int width, int height);


#endif
