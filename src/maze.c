#include <stdlib.h>
#include "maze.h"

maze_t *init_maze(size_t cols, size_t rows, int cell_size, int line_weight) {
	maze_t *maze = malloc(sizeof(maze_t));
	if (maze == NULL)
		return NULL;

	maze->cell_size = cell_size;
	maze->line_weight = line_weight;
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

	return maze;
}

cell_t *cell_at(maze_t *maze, int x, int y) {
	return maze->cells + maze->cols * y + x;
}

bitmap_t *maze_to_img(maze_t *maze, int scale) {
	bitmap_t *bitmap = malloc(sizeof(bitmap_t));
	if (bitmap == NULL)
		return NULL;
	
	bitmap->width = (maze->cols * maze->cell_size * scale);
	bitmap->height = (maze->rows * maze->cell_size * scale);
	bitmap->pixels = calloc(bitmap->width * bitmap->height, sizeof(pixel_t));
	
	for (int x = 0; x < bitmap->width; x++) {
		for (int y = 0; y < bitmap->height; y++) {
			cell_t *cell = cell_at(maze, (x / maze->rows) % maze->rows, (y / maze->cols) % maze->cols);
			if (cell == NULL)
				return NULL;
		
			pixel_t *pixel = pixel_at(bitmap, x, y);
			// TOP
			if (cell->top) {
				if ((x >= cell->x * maze->cell_size) && 
					(x < (cell->x + 1) * maze->cell_size) &&
					(y <= (cell->y * maze->cell_size * scale) + maze->line_weight) &&
					(y > cell->y * maze->cell_size * scale) - maze->line_weight) {
						pixel->red = 0;
						pixel->green = 0;
						pixel->blue = 255;	
				}
			}
			//RIGHT
			if (cell->right) {
				if ((y >= cell->y * maze->cell_size) && 
					(y < (cell->y + 1) * maze->cell_size) &&
					(x <= ((cell->x + 1) * maze->cell_size * scale) + maze->line_weight) &&
					(x > cell->x * maze->cell_size * scale) - maze->line_weight) {
						pixel->red = 0;
						pixel->green = 0;
						pixel->blue = 255;	
				}
			}
			// LEFT
			/*
			if (cell->left) {
				if ((y >= cell->y * maze->cell_size) && 
					(y < (cell->y + 1) * maze->cell_size) &&
					(x <= (cell->x * maze->cell_size * scale) + maze->line_weight) &&
					(x > cell->x * maze->cell_size * scale) - maze->line_weight) {
						pixel->red = 0;
						pixel->green = 0;
						pixel->blue = 255;	
				}
			}
			*/
			else {
				pixel->red = 0;
				pixel->green = 0;
				pixel->blue = 0;
			}
			// RIGHT
			// BOTTOM
			// LEFT
		}
	}

	return bitmap;
}
