#include <stdlib.h>
#include "maze.h"

maze_t *init_maze(size_t cols, size_t rows, int cell_size) {
	maze_t *maze = malloc(sizeof(maze_t));
	if (maze == NULL)
		return NULL;

	maze->cell_size = cell_size;
	maze->cols = cols;
	maze->rows = rows;
	maze->cells = calloc(rows * cols, sizeof(cell_t));

	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < rows; y++) {
			cell_t *cell = cell_at(maze, x, y);
			if (cell == NULL)
				return NULL;
			cell->x = x;
			cell->y = y;
			cell->top = true;
			cell->right = true;
			cell->bottom = true;
			cell->left = true;
			cell->visited = false;
		}
	}

	return maze;
}

cell_t *cell_at(maze_t *maze, int x, int y) {
	if (x < 0 || y < 0 || x > maze->cols - 1 || x > maze->rows - 1)
		return NULL;
	return maze->cells + maze->cols * y + x;
}

cell_t *check_neighbors(maze_t *maze, cell_t *cell) {
	int x = cell->x;
	int y = cell->y;

	cell_t *neighbors[4] = { cell_at(maze, x, y - 1),
						cell_at(maze, x + 1, y),
						cell_at(maze, x, y + 1),
						cell_at(maze, x - 1, y)	};
	
	int random_num = rand() % 4;

	for (int i = 0; i < 4; i++) {
		//printf("%i\n", (random_num + i) % 4);
		cell_t *random_neighbor = neighbors[(random_num + i) % 4];
		if (random_neighbor && !random_neighbor->visited) {
			random_neighbor->visited = true;
			check_neighbors(maze, random_neighbor);
			return random_neighbor;
		}
	}

	return NULL;
}

maze_t *create_maze(maze_t *maze, cell_t *current) {
	current->visited = true;
	srand(time(NULL));
	
	check_neighbors(maze, current);

	return maze;
}

bitmap_t *maze_to_img(maze_t *maze, int scale) {
	bitmap_t *bitmap = malloc(sizeof(bitmap_t));
	if (bitmap == NULL)
		return NULL;
	
	bitmap->width = ((maze->cols * maze->cell_size) + maze->cols * 2) * scale;
	bitmap->height = ((maze->rows * maze->cell_size) + maze->rows * 2) * scale;
	bitmap->pixels = calloc(bitmap->width * bitmap->height, sizeof(pixel_t));
	
	for (int x = 0; x < bitmap->width; x++) {
		for (int y = 0; y < bitmap->height; y++) {
			cell_t *cell = cell_at(maze, (x / ((maze->cell_size + 2) * scale)) % maze->rows, (y / ((maze->cell_size + 2) * scale)) % maze->cols);
			if (cell == NULL)
				return NULL;

			pixel_t *pixel = pixel_at(bitmap, x, y);
			// TOP
			if (cell->top && (y == (cell->y * (maze->cell_size + 2) * scale))) {
				pixel->red = 255;
				pixel->green = 0;
				pixel->blue = 0;	
			}
			// RIGHT
			else if (cell->right && (x == ((cell->x + 1) * (maze->cell_size + 2) * scale) - 1)) {
				pixel->red = 255;
				pixel->green = 0;
				pixel->blue = 0;	
			}
			// BOTTOM
			else if (cell->bottom && (y == ((cell->y + 1) * (maze->cell_size + 2) * scale) - 1)) {
				pixel->red = 255;
				pixel->green = 0;
				pixel->blue = 0;	
			}
			// LEFT
			else if (cell->left && (x == (cell->x * (maze->cell_size + 2) * scale))) {
				pixel->red = 255;
				pixel->green = 0;
				pixel->blue = 0;	
			}	
			else if (cell->visited) {
				pixel->red = 0;
				pixel->green = 255;
				pixel->blue = 0;
			}
			else {
				pixel->red = 0;
				pixel->green = 0;
				pixel->blue = 0;
			}
		}
	}

	return bitmap;
}
