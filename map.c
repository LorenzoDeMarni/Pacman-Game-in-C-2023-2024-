// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdlib.h>
#include <stdio.h>
#include "defines.h"
#include "colours.h"
#include "map.h"
#include <string.h>

extern char *map, *dot_map;
extern int width, height;



// Function to print the map
void print_map(void){
    // print the map and account for outer walls
    for (int i = 0; i < height + 2; i++){
        for (int j = 0; j < width + 2; j++){
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1){
                // print outer walls
                change_text_colour(BLUE);
                printf("%2c", WALL);
            }
            else{
                if (map[(i - 1) * width + (j - 1)] == DOT){
                    change_text_colour(WHITE);
                }
                else if (map[(i - 1) * width + (j - 1)] == WALL){
                    change_text_colour(BLUE);
                }
                else if (map[(i - 1) * width + (j - 1)] == GHOST){
                    change_text_colour(PINK);
                }
                else if (map[(i - 1) * width + (j - 1)] == PACMAN){
                    change_text_colour(YELLOW);
                }
                printf("%2c", map[(i - 1) * width + (j - 1)]);
            }
        }
        printf("\n");
    }
    change_text_colour(WHITE); // reset text colour to white
    
}


int move_actor(int *y, int *x, char direction, int eat_dots) {
    int new_x = *x, new_y = *y; // initialize new_x and new_y to the current x and y coordinates

    // update new_x and new_y based on the direction
    switch (direction){
        case LEFT:
            new_x = *x - 1;
            break;
        case RIGHT:
            new_x = *x + 1;
            break;
        case UP:
            new_y = *y - 1;
            break;
        case DOWN:
            new_y = *y + 1;
            break;
        default:
            return MOVED_INVALID_DIRECTION;
    }

    if (is_wall(new_y, new_x) == NOT_WALL && new_x >= 0 && new_x < width && new_y >= 0 && new_y < height){ // if the new position is not a wall and is within the bounds of the map
        if (eat_dots == REPLACE_DOTS){ // for ghosts
            map[*y * width + *x] = dot_map[*y * width + *x]; // replace dot or empty  in map array if actor is a ghost
            map[new_y * width + new_x] = GHOST; // update map to show ghost

        }
        else if (eat_dots == EAT_DOTS){ // for pacman
            // if pacman moves into a ghost, dont let pacman move because the ghost will have eaten pacman
            if (map[new_y * width + new_x] == GHOST){
                return MOVED_OKAY;
            }
            dot_map[new_y * width + new_x] = EMPTY; // update dot map to remove the dot at new position
            map[*y * width + *x] = dot_map[*y * width + *x]; // update map to remove pacman at old position
            map[new_y * width + new_x] = PACMAN; // update map to show pacman at new position
        }
        else{
            return MOVED_INVALID_DIRECTION;
        }
        
        // update x and y coordinates
        (*x) = new_x;
        (*y) = new_y;
        
        return MOVED_OKAY;
    }
    else{
        return MOVED_WALL;
    }
}
int is_wall(int y, int x) {
    if (x < 0 || x >= width || y < 0 || y >= height){ // if coordinates are off the map
        return NOT_WALL;
    }
    
    if (map[y * width + x] == WALL){ // if character at coords y,x in map is a wall, return YES_WALL
        return YES_WALL;
    }
    
    return NOT_WALL;
}


char *load_map(char *filename, int *map_height, int *map_width) {
    // open the file pointer for reading and check it doesn't contain NULL
    FILE *fPointerRead = fopen(filename, "r");
    if (fPointerRead == NULL){
        return NULL;
    }


    //initialize the value of map height and width to 0
    *map_width = 0;
    *map_height = 0;

    char character;
    char *tempMap = NULL;
    int counter = 1; // counter variable which increases by one for every character added
    // calculate the height and width of the map using while loop
    while ((character = (char) fgetc(fPointerRead)) != EOF){ // read until the end of the file
        if (character == '\n'){ // if the character is a new line, increment the height 
            (*map_height)++;
        }
        else if (character != ' '){ // check for non-empty char in text file
            if (*map_height == 0) // width only needs to be calculated for first line
                (*map_width)++;

            char *newTempMap = (char *) realloc(tempMap, (counter + 1) * sizeof(char)); // reallocate new memory for map which contains the map being updated

            if (newTempMap == NULL){ // if the reallocation fails
                fclose(fPointerRead); // close the file pointer
                free(tempMap); // free the memory allocated for the map
                
                return NULL;
            }

            tempMap = newTempMap;
            tempMap[counter - 1] = character; // add character into map
            counter++; // increase total size of the array counter

        }
    }

    (*map_height)++; // account for the last line

    // set global height and width
    width = *map_width;
    height = *map_height;


    // close the file pointer and return the map character array
    fclose(fPointerRead);
    return tempMap;

}
