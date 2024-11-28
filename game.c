// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

extern char * map, * dot_map;
extern int height;
extern int width;

int check_win(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    int dotsLeft = 0; // initialize dots_left to 0
    for (int i = 0; i < height; i++){ // loop through the rows of the map
        for (int j = 0; j < width; j++){ // loop through the columns of the map
            if (dot_map[i * width + j] == DOT){ 
                dotsLeft++; // increment dotsLeft if there is a dot in the current position
            }
        }
    }
    if (dotsLeft == 0){
        for (int i = 0; i < NUM_GHOSTS; i++) { // loop through the ghosts
            if (pacman_y == ghosts_y[i] && pacman_x == ghosts_x[i]){
                return KEEP_GOING; // pacman is in the same position as a ghost, game is a loss but continues
            }
        }
        return YOU_WIN; // no dots left and Pacman is not in the same position as any ghost, you win
    }
    return KEEP_GOING; // return keep going if the game is not over
}

int check_loss(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    for (int i = 0; i < NUM_GHOSTS; i++){ // loop through the ghosts
        if (pacman_y == ghosts_y[i] && pacman_x == ghosts_x[i]){
            return YOU_LOSE; // return you lose if pacman is in the same position as any of the ghosts
        }
    }
    return KEEP_GOING; // return keep going if the game is not over
}

