#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "maze.h"
   
int main ()
{
    bitmap_t *maze = init_maze(1000, 1000);
    int x;
    int y;
    int status = 0;

    if (! maze->pixels) {
	return -1;
    }

    for (y = 0; y < maze->height; y++) {
        for (x = 0; x < maze->width; x++) {
            pixel_t *pixel = pixel_at(maze, x, y);
            pixel->red = pix(255, maze->width);
            pixel->blue = pix (255, maze->height);
        }
    }

	pixel_t *pixel = pixel_at(maze, 50, 50);
	pixel->red = 255;
	pixel->blue = 255;
	pixel->green = 255;




    if (save_png_to_file (maze, "maze.png")) {
	fprintf (stderr, "Error writing file.\n");
	status = -1;
    }

    free (maze->pixels);

    return status;
}
