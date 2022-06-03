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
		}
	}

	cell_t *cell = cell_at(maze, 2, 2);
	cell->top = false;

	return maze;
}

cell_t *cell_at(maze_t *maze, int x, int y) {
	return maze->cells + maze->cols * y + x;
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
			cell_t *cell = cell_at(maze, (x / (maze->cell_size * 2 * scale)) % maze->rows, (y / (maze->cell_size * 2 * scale)) % maze->cols);
			if (cell == NULL)
				return NULL;
			
			pixel_t *pixel = pixel_at(bitmap, x, y);
			// TOP
			if (cell->top && (y == (cell->y * maze->cell_size * 2 * scale))) {
				pixel->red = 255;
				pixel->green = 0;
				pixel->blue = 0;	
			}
			// RIGHT
			else if (cell->right && (x == ((cell->x + 1) * maze->cell_size * 2 * scale) - 1)) {
				pixel->red = 255;
				pixel->green = 0;
				pixel->blue = 0;	
			}
			// BOTTOM
			else if (cell->bottom && (y == ((cell->y + 1) * maze->cell_size * 2 * scale) - 1)) {
				pixel->red = 255;
				pixel->green = 0;
				pixel->blue = 0;	
			}
			// LEFT
			else if (cell->left && (x == (cell->x * maze->cell_size * 2 * scale))) {
				pixel->red = 255;
				pixel->green = 0;
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
