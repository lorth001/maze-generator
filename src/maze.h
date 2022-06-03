#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>
#include "image.h"

typedef struct {
	pixel_t *pixels;
	int x;
	int y;
	bool top;
	bool right;
	bool bottom;
	bool left;
	bool visited;
} cell_t;

typedef struct {
	cell_t *cells;
	int cell_size;
	int cols;
	int rows;
} maze_t;

cell_t *cell_at(maze_t *maze, int x, int y);

maze_t *init_maze(size_t cols, size_t rows, int cell_size);

bitmap_t *maze_to_img(maze_t *maze, int scale);

cell_t *check_neighbors(maze_t *maze, cell_t *cell);

maze_t *create_maze(maze_t *maze, cell_t *current);

#endif
