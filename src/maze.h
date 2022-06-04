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
	bool current;
} cell_t;

typedef struct {
	cell_t *cells;
	int cell_size;
	int cols;
	int rows;
} maze_t;

typedef struct {
	int top;
	int capacity;
	cell_t **items;
} stack_t;

cell_t *cell_at(maze_t *maze, int x, int y);

maze_t *init_maze(size_t cols, size_t rows, int cell_size);

stack_t *init_stack(int capacity);

void push(stack_t *stack, cell_t *cell);

cell_t *pop(stack_t *stack);

bool is_empty(stack_t *stack);

int maze_to_img(maze_t *maze, int count, int scale);

void remove_walls(cell_t *cell_a, cell_t *cell_b);

cell_t *check_neighbors(maze_t *maze, stack_t *visited, cell_t *cell, int iter);

maze_t *create_maze(maze_t *maze, int x, int y);

#endif
