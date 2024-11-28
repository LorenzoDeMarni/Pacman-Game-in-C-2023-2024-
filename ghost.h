// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#ifndef PROJECT_GHOST_H
#define PROJECT_GHOST_H

/** Functions required to be implemented **/

#define SEES_NOTHING 0
#define EATING_PACMAN 1
/**
 * Checks if a ghost can see pacman, and in what direction they must
 * look to see him.
 * This function should use the passed coordinates of pacman and one
 * ghost to see if the ghost can see pacman by looking in a straight
 * line without looking through a wall.  The function can assume that
 * the global map / height / width are valid.
 *
 * If the ghost can see pacman without looking through a wall, the
 * function should return a direction that the ghost must look to see
 * him (LEFT, RIGHT, UP, DOWN) as defined in defines.h.  If the ghost
 * is eating pacman, the function should return EATING_PACMAN.  If
 * the ghost cannot see pacman, the function should return SEES_NOTHING.
 * @param pacman_y Pacman's Y coordinate
 * @param pacman_x Pacman's X coordinate
 * @param ghost_y The ghost's Y coordinate
 * @param ghost_x The ghost's X coordinate
 * @return The direction the ghost must look to see pacman, if possible.
 *         Otherwise, a status code.
 */
char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x);

/** Other function prototypes can go below here **/


#endif //PROJECT_GHOST_H
