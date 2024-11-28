// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "ghost.h"
#include "map.h"
extern int height;
extern int width;
extern char * map;
char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x) {
    if (pacman_y == ghost_y && pacman_x == ghost_x){ 
        return EATING_PACMAN; // if pacman and ghost are in the same position, return eating pacman
    }
    
    if (pacman_y == ghost_y){ // if pacman and ghost are on the same row
        if (pacman_x > ghost_x){ // if pacman is to the right of the ghost
            for (int i = ghost_x; i < pacman_x; i++){ // loop through the columns between the ghost and pacman
                if (map[ghost_y*width + i] == WALL){ // if there is a wall between the ghost and pacman
                    return SEES_NOTHING; 
                }
            }
            return RIGHT; // return right if pacman is to the right of the ghost
        }
        else{ // if pacman is to the left of the ghost
            for (int i = pacman_x; i < ghost_x; i++){ // loop through the columns between the ghost and pacman
                if (map[ghost_y*width + i] == WALL){ // if there is a wall between the ghost and pacman
                    return SEES_NOTHING; 
                }
            }
            return LEFT; // return left if pacman is to the left of the ghost
        }
    }
    else if (pacman_x == ghost_x){ // if pacman and ghost are on the same column
        if (pacman_y > ghost_y){ // if pacman is below the ghost
            for (int i = ghost_y; i < pacman_y; i++){ // loop through the rows between the ghost and pacman
                if (map[i*width + ghost_x] == WALL){ // if there is a wall between the ghost and pacman
                    return SEES_NOTHING;
                }
            }
            return DOWN; // return down if pacman is below the ghost
        }
        else{ // if pacman is above the ghost
            for (int i = pacman_y; i < ghost_y; i++){ // loop through the rows between the ghost and pacman
                if (map[i*width + ghost_x] == WALL){ // if there is a wall between the ghost and pacman
                    return SEES_NOTHING;
                }
            }
            return UP; // return up if pacman is above the ghost
        }
    }
    else{ // if pacman and ghost are not on the same row or column
        return SEES_NOTHING;
    }
    
}
