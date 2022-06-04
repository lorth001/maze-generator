#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "maze.h"
   
int main ()
{
	maze_t *maze = init_maze(100, 100, 1);

	maze = create_maze(maze, 0, 0);

    free(maze->cells);
	free(maze);

    return 0;
}
