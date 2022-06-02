#include <stdlib.h>
#include "image.h"

bitmap_t *init_maze(int width, int height) {
	bitmap_t *bitmap = malloc(sizeof(bitmap_t));
	if (bitmap == NULL)
		return NULL;

	bitmap->width = width;
	bitmap->height = height;
	bitmap->pixels = calloc(width * height, sizeof(pixel_t));
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pixel_t *pixel = pixel_at(bitmap, i, j);
			pixel->red = 0;
			pixel->green = 0;
			pixel->blue = 0;
		}
	}

	return bitmap;
}
