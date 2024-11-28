// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

/** Functions required to be implemented **/

/**
 * Loads a map file into an array allocated dynamically to store it.
 * The function must allocate space using malloc/realloc and load
 * the map file contents into it.  The return value is the pointer
 * to the allocated and populated memory, and the height/width values
 * that are returned via the map_height/map_width pass-by-reference
 * parameters.
 *
 * The function can assume that the parameters are valid pointers, but
 * it should not assume that the file exists.  The map file format
 * is #__#__# ... __# where the # are symbols and _ represent whitespace
 * which should be ignored.  That is, the function can assume that
 * symbols are each separated by two spaces.  The function MAY NOT
 * assume that the map is a specific size; it must properly load any
 * size map in the correct format.  It can assume that the only valid
 * symbols are DOT, PACMAN, GHOST, WALL, and EMPTY as defined in
 * defines.h.  The function can assume that the map is a rectangle.
 *
 * On error, the function should return NULL and should not write to
 * map_height or map_width.
 *
 * For example, if the map file contains the map:
 * .  P  .  .
 * W     W  W
 * G  .  .  G
 * Then the function should return a dynamically allocated array:
 * {'.', 'P', '.', '.', 'W', ' ', 'W', 'W', 'G', '.', '.', 'G'}
 * and set *map_height = 3, *map_width = 4.
 *
 * @param filename A string containing the map file name to read
 * @param map_height A pointer to where the map height should be stored
 * @param map_width A pointer to where the map width should be stored
 * @return A pointer to the loaded map, or NULL on error
 */
char * load_map(char * filename, int * map_height, int *map_width);

#define NOT_WALL 0
#define YES_WALL 1
/**
 * Determines if a coordinate in the map is a wall or not.
 * This function should use the global map and the passed coordinates
 * to determine a yes/no answer if this coordinate is a wall.
 *
 * You should use the above #defines for return values from
 * this function.  This function can assume that the global map
 * and its height/width are all valid.
 *
 * @param y The Y coordinate on the map to check
 * @param x The X coordinate on the map to check
 * @return NOT_WALL if the coordinate is not a wall, YES_WALL if it is
 */
int is_wall(int y, int x);

#define MOVED_OKAY 0
#define MOVED_WALL 1
#define MOVED_INVALID_DIRECTION 2
#define REPLACE_DOTS 0
#define EAT_DOTS 1
/**
 * Try to move an actor at the given coordinates, respecting walls and
 * updating the map to replace a dot if required.
 * This function is passed the coordinates of an "actor", where that
 * could be pacman or a ghost.  The function also takes a direction that
 * the actor should move (UP, DOWN, LEFT, RIGHT) defined in defines.h.
 * The coordinates are passed by reference so that they can be updated
 * by the function, while the return of the function is a status code.
 * The function also takes a parameter to either update the global map
 * with dots from the global dot_map (REPLACE_DOTS) or not (EAT_DOTS),
 * in which case the vacated coordinates should be replaced by EMPTY.
 * In either case, the global map should be updated at the passed
 * coordinates, but not at the new coordinates, if moving was successful.
 *
 * If the actor cannot move because it would run into a wall, the
 * function should return MOVED_WALL and not update the map or the
 * coordinate pointers.  If the direction that was passed was not a
 * valid direction, the function should return MOVED_INVALID_DIRECTION.
 * If the function successfully moves the actor, it should return
 * MOVED_OKAY.
 *
 * @param y A pointer to the Y position of the actor to move
 * @param x A pointer to the X position of the actor to move
 * @param direction The direction to try to move
 * @param eat_dots Whether or not to update the map from the dot map
 * @return A status code depending on the result of the function
 */
int move_actor(int * y, int * x, char direction, int eat_dots);

/** Other function prototypes can go below here **/

void print_map(void);





#endif //PROJECT_MAP_H
