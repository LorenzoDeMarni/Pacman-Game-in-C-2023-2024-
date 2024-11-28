// APSC 142 Engineering Programming Project Starter Code
// cSpell:words APSC Kauffman PACMAN pacman
// Copyright Sean Kauffman 2024

// don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
#include <stdio.h>
#include <stdlib.h>

// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"

// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and ghost.h contain prototypes of functions you must implement
#include "map.h"
#include "game.h"
#include "ghost.h"

// These global variables must be used to store map information.
// Almost every function needs these variables, so keeping them as globals helps keep things organized.
// map is a pointer to a dynamically allocated map for displaying to the user
// dot_map is a pointer to a dynamically allocated map for keeping track of what dots are left
char *map, *dot_map;
// width and height store the width and height of map, NOT counting outer walls
int width, height;

/**
 * Main entry point into your program.
 * Make sure that main returns appropriate status codes depending on what
 * happens.  The codes you must use are:
 *   NO_ERROR when no error occurs
 *   ERR_NO_MAP when no map file is found
 *   ERR_NO_PACMAN when no pacman is found on the map
 *   ERR_NO_GHOSTS when fewer than 2 ghosts are found on the map
 *
 * Make sure that any allocated memory is freed before returning.
 * @return a status code
 */
int main(void) {
    setbuf(stdout, NULL);

    //create pointers to store the map height and width
    int* map_height = malloc(sizeof(int));
    int* map_width = malloc(sizeof(int));

    // Load the map from the file "map.txt"
    map = load_map("map.txt", map_height, map_width); // load the map from the file
    if (map == NULL){
        free(map_height);
        free(map_width);
        free(map);
        return ERR_NO_MAP;
    }
    
    // allocate memory for the dot_map
    dot_map = (char*)malloc(width * height * sizeof(char));

    // loop through the map and add dots to the dot map
    for(int i = 0; i < width * height; i++){ 
        if (map[i] == DOT){
            dot_map[i] = DOT;
        }
        else{
            dot_map[i] = EMPTY;
        }
    }
    int ghosts_x[NUM_GHOSTS], ghosts_y[NUM_GHOSTS]; // declare arrays to store the ghost positions
    int num_ghosts = 0; // initialize the number of ghosts to 0
    int pacman_y = -1, pacman_x = -1; // initialize pacman's position to -1
    // find pacman and ghosts in the map and store their positions
    for(int i=0; i<height; i++){
        for(int j=0;j<width;j++){
            if(map[i*height + j] == PACMAN){
                pacman_x = j;
                pacman_y = i;
            }
            if(map[i*height + j] == GHOST){
                ghosts_x[num_ghosts] = j;
                ghosts_y[num_ghosts] = i;
                num_ghosts++; // increment the number of ghosts found
            }
        }
    }
    if (pacman_x == -1 || pacman_y == -1){ 
        free(map_height);
        free(map_width);
        free(map);
        free(dot_map);
        printf("No pacman found\n");
        return ERR_NO_PACMAN; // if pacman is not found, return error
    }
    if (num_ghosts < 2){
        free(map_height);
        free(map_width);
        free(map);
        free(dot_map);
        printf("Less than %d ghosts found\n", NUM_GHOSTS);  
        return ERR_NO_GHOSTS; // if there are fewer than 2 ghosts, return error
        
    }


    // GAME LOOP
    int gameStatus = KEEP_GOING; // initialize game status to keep going
    while(gameStatus == KEEP_GOING){
        // print the map and account for outer walls and with colours
        print_map();

        // check win condition first
        gameStatus = check_win(pacman_y, pacman_x, ghosts_y, ghosts_x);
        if (gameStatus == YOU_WIN){
            printf("You win!\n");
            break;
        }
        gameStatus = check_loss(pacman_y, pacman_x, ghosts_y, ghosts_x);
        if (gameStatus == YOU_LOSE){
            printf("Sorry, you lose.\n");
            break;
        }

        // move pacman using input from the user
        printf("Enter a move:");
        char move=(char)getch();
        printf("\n");
        
        // move pacman
        move_actor(&pacman_y, &pacman_x, move, EAT_DOTS);

        // move ghosts
        char random_directions[4] = {UP, DOWN, LEFT, RIGHT}; // array of random directions
        // loop through each ghost and move them based on their position relative to pacman
        for (int i = 0; i < num_ghosts; i++){
            char direction = sees_pacman(pacman_y, pacman_x, ghosts_y[i], ghosts_x[i]);
            if (direction != SEES_NOTHING){ // if the ghost sees pacman, move towards pacman
                move_actor(&ghosts_y[i], &ghosts_x[i], direction, REPLACE_DOTS);
            }
            else{
                while(1){ // loop until a valid random move is made for the ghost
                    int random_index = rand() % 4;
                    if (move_actor(&ghosts_y[i], &ghosts_x[i], random_directions[random_index], REPLACE_DOTS) == MOVED_OKAY){
                        break; // break the loop if a valid move is made
                    }
                }
            }
        }
    }
    // free the memory 
    free(map_height);
    free(map_width);
    free(map);
    free(dot_map);

    return NO_ERROR;
}
