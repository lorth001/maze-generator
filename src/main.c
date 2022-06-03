#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "maze.h"
   
int main ()
{
	maze_t *maze = init_maze(20, 20, 10);
    bitmap_t *bitmap = maze_to_img(maze, 5);

    if (save_png_to_file (bitmap, "maze.png")) {
	fprintf (stderr, "Error writing file.\n");
    }

    free(maze->cells);
	free(maze);
	free(bitmap->pixels);
	free(bitmap);

    return 0;
}
