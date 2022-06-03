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

void remove_walls(cell_t *cell_a, cell_t *cell_b) {
	int delta_x = cell_a->x - cell_b->x;
	int delta_y = cell_a->y - cell_b->y;

	// X
	if (delta_x == 1) {
		cell_a->left = false;
		cell_b->right = false;
	}
	else if (delta_x == -1) {
		cell_a->right = false;
		cell_b->left = false;
	}

	// Y
	if (delta_y == 1) {
		cell_a->top = false;
		cell_b->bottom = false;
	}
	else if (delta_y == -1) {
		cell_a->bottom = false;
		cell_b->top = false;
	}
}

cell_t *check_neighbors(maze_t *maze, cell_t *cell, int count) {
	cell_t *start = cell_at(maze, 0, 0);
	printf("x: %i, y: %i, top: %i, right: %i, bottom: %i, left: %i, visited: %i\n", start->x, start->y, start->top, start->right, start->bottom, start->left, start->visited);
	int x = cell->x;
	int y = cell->y;

	cell_t *neighbors[4] = { cell_at(maze, x, y - 1),
						cell_at(maze, x + 1, y),
						cell_at(maze, x, y + 1),
						cell_at(maze, x - 1, y)	};
	
	int random_num = rand() % 4;

	for (int i = 0; i < 4; i++) {
		cell_t *random_neighbor = neighbors[(random_num + i) % 4];
		if (random_neighbor && !random_neighbor->visited) {
			printf("\n\nCOUNT: %i\ncell->x: %i, cell->y: %i, visited: %i\nneighbor->x: %i, neighbor->y: %i, visited: %i\n", count, cell->x, cell->y, cell->visited, random_neighbor->x, random_neighbor->y, random_neighbor->visited);
			random_neighbor->visited = true;
			remove_walls(cell, random_neighbor);
			maze_to_img(maze, count, 5);
			
			check_neighbors(maze, random_neighbor, ++count);
			return random_neighbor;
		}
	}

	return NULL;
}

maze_t *create_maze(maze_t *maze, int x, int y) {
	cell_t *start = cell_at(maze, 0, 0);
	printf("x: %i, y: %i, top: %i, right: %i, bottom: %i, left: %i, visited: %i\n", start->x, start->y, start->top, start->right, start->bottom, start->left, start->visited);
	start->visited = true;
	srand(time(NULL));
	
	printf("x: %i, y: %i, top: %i, right: %i, bottom: %i, left: %i, visited: %i\n", start->x, start->y, start->top, start->right, start->bottom, start->left, start->visited);
	check_neighbors(maze, start, 0);

	system("ffmpeg -i maze_%d.png -vcodec libx265 -crf 28 -filter:v 'setpts=3.0*PTS' video.mp4 >null 2>null");

	return maze;
}

int maze_to_img(maze_t *maze, int count, int scale) {
	bitmap_t *bitmap = malloc(sizeof(bitmap_t));
	if (bitmap == NULL)
		return -1;
	
	bitmap->width = ((maze->cols * maze->cell_size) + maze->cols * 2) * scale;
	bitmap->height = ((maze->rows * maze->cell_size) + maze->rows * 2) * scale;
	bitmap->pixels = calloc(bitmap->width * bitmap->height, sizeof(pixel_t));
	
	for (int x = 0; x < bitmap->width; x++) {
		for (int y = 0; y < bitmap->height; y++) {
			cell_t *cell = cell_at(maze, (x / ((maze->cell_size + 2) * scale)) % maze->rows, (y / ((maze->cell_size + 2) * scale)) % maze->cols);
			if (cell == NULL)
				return -1;

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

	char filename[32];
	sprintf(filename, "maze_%i.png", count);
	save_png_to_file(bitmap, filename);

	free(bitmap->pixels);
	free(bitmap);

	return 0;
}
