// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

/** Functions required to be implemented **/

#define KEEP_GOING 0
#define YOU_WIN 1
/**
 * Returns if the game has been won or not.
 * Checks the global maps to see if all the dots have been eaten.
 * If no dots remain, then it should return YOU_WIN.  If not,
 * then it should return KEEP_GOING.  The function can assume
 * that the global map and width/height are valid.
 * @param pacman_y The Y coordinate of pacman
 * @param pacman_x The X coordinate of pacman
 * @param ghosts_y An array of Y coordinates of ghosts
 * @param ghosts_x An array of X coordinates of ghosts
 * @return YOU_WIN if no dots remain, otherwise KEEP_GOING
 */
int check_win(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]);

#define YOU_LOSE 1
/**
 * Returns if the game has been lost or not.
 * Compares the positions of the ghosts with the position of
 * pacman to see if pacman has been eaten.  If so, the function
 * should return YOU_LOSE.  If not, it should return KEEP_GOING.
 *
 * The ghosts_y and ghosts_x arrays are meant to hold NUM_GHOSTS
 * coordinates.  So, index 0 of ghosts_x holds the X coordinate
 * of ghost 0 and index 0 of ghosts_y holds the Y coordinate of
 * ghost 0.
 * @param pacman_y The Y coordinate of pacman
 * @param pacman_x The X coordinate of pacman
 * @param ghosts_y An array of Y coordinates of ghosts
 * @param ghosts_x An array of X coordinates of ghosts
 * @return
 */
int check_loss(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]);

/** Other function prototypes can go below here **/


#endif //PROJECT_GAME_H
