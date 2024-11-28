// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C"{
#include "defines.h"
#include "map.h"
#include "ghost.h"
#include "game.h"
char *map = NULL, *dot_map = NULL;
int width, height;
}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

void setup(void) {
    //call load map of map.txt


    // Load the map from the file "map.txt"
    map = load_map("map.txt", &height, &width); // load the map from the file
    if (map == NULL) {
        printf("Error loading map\n");
        return;
    }
    // Allocate memory for the dot map
    dot_map = (char *)malloc(width * height * sizeof(char));
    if (dot_map == NULL) {
        printf("Error allocating memory\n");
        return;
    }
    // Copy the map to the dot map
    for (int i = 0; i < width * height; i++) {
        dot_map[i] = map[i];
    }

    

}

void teardown(void) {
    free(map);
    free(dot_map);

}

/* tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// tests for load_map
TEST_CASE("A test for load_map") {
    setup();
    CHECK(map[0] == GHOST); // check if the first character is a ghost
    CHECK(map[1] == DOT); // check if the second character is a dot
    CHECK(map[4] == WALL); // check if the fifth character is a wall
    CHECK(map[40] == PACMAN); // check if the 41st character is pacman
    CHECK(width == 9); // check if the width is 9
    CHECK(height == 9); // check if the height is 9
    
    teardown();
}

// tests for is_wall
TEST_CASE("A test for is_wall") {
    setup();
    CHECK(is_wall(0,1) == NOT_WALL); // check if the wall is not a wall
    CHECK(is_wall(1,1) == YES_WALL); // check if the wall is a wall
    CHECK(is_wall(-1,-1) == NOT_WALL); // check if the wall is a wall

    teardown();
}
// tests for move_actor
TEST_CASE("A test for move_actor") {
    setup();
    int tempx;
    int tempy;
    tempx = 0;
    tempy = 0;
    CHECK(move_actor(&tempy,&tempx, LEFT, REPLACE_DOTS) == 1);
    CHECK(move_actor(&tempy,&tempx, UP, REPLACE_DOTS) == 1);
    CHECK(move_actor(&tempy,&tempx, RIGHT, REPLACE_DOTS) == 0);
    CHECK(move_actor(&tempy,&tempx, DOWN, REPLACE_DOTS) == 1);
    tempx = 4;
    tempy = 4;
    CHECK(move_actor(&tempy,&tempx, UP, EAT_DOTS) == 1);
    CHECK(move_actor(&tempy,&tempx, DOWN, EAT_DOTS) == 1);
    CHECK(move_actor(&tempy,&tempx, RIGHT, EAT_DOTS) == 0);
    CHECK(move_actor(&tempy,&tempx, LEFT, EAT_DOTS) == 0);
    teardown();
}




// tests for sees pacman
TEST_CASE("A test for sees_pacman") {
    setup();
    CHECK(sees_pacman(0, 2, 0, 0) == RIGHT); // check if pacman is to the right of the ghost
    CHECK(sees_pacman(4,4, 0, 0) == SEES_NOTHING); // check if pacman is not in the ghost's line of sight
    CHECK(sees_pacman(4,4, 2, 4) == SEES_NOTHING); // check if ghost cannot see pacman through a wall
    CHECK(sees_pacman(0,0,0,0) == EATING_PACMAN); // check if ghost is eating pacman
    CHECK(sees_pacman(2, 0, 0, 0) == DOWN); // check if pacman is to the up of the ghost
    CHECK(sees_pacman(0, 0, 0, 2) == LEFT); // check if pacman is to the left of the ghost
    CHECK(sees_pacman(0, 0, 2, 0) == UP); // check if pacman is to the down of the ghost



    teardown();
}
TEST_SUITE_END();

/* tests for game.c */

TEST_SUITE_BEGIN("Game tests");

// tests for check_win
TEST_CASE("A test for check_win") {
    setup();
    int ghosts_x[] = {0, 8};
    int ghosts_y[] = {0, 8};
    int pacman_x = 4;
    int pacman_y = 4;
    // check if pacman has not won yet
    CHECK(check_win(pacman_y, pacman_x, ghosts_y, ghosts_x) == KEEP_GOING); 
    
    // remove all dots from dot map
    for(int i=0;i<height*width;i++){
        dot_map[i] = EMPTY;
    }

    int new_ghosts_x[] = {4, 8};
    int new_ghosts_y[] = {4, 8};

    // check if pacman has not won yet, in this case user has collected all dots but still lost the game, so pacman has not won

    CHECK(check_win(pacman_y, pacman_x, new_ghosts_y, new_ghosts_x) == KEEP_GOING);
    
    int final_ghosts_x[] = {0, 8};
    int final_ghosts_y[] = {0, 8};

    
    // check if pacman has won, all dots have been collected and pacman and ghosts are not in the same position
    CHECK(check_win(pacman_y, pacman_x, final_ghosts_y, final_ghosts_x) == YOU_WIN);
    teardown();
}

// test for check_loss
TEST_CASE("A test for check_loss") {
    setup();
    int ghosts_x[2] = {0, 8};
    int ghosts_y[2] = {0, 8};
    int pacman_x = 4;
    int pacman_y = 4;

    // check if pacman has not lost yet as pacman and ghost are not in the same position
    CHECK(check_loss(pacman_y, pacman_x, ghosts_y, ghosts_x) == KEEP_GOING);

    int new_ghosts_x[2] = {4,8};
    int new_ghosts_y[2] = {4,8};
    // check if pacman has lost, pacman and ghost are in the same position
    CHECK(check_loss(pacman_y, pacman_x, new_ghosts_y, new_ghosts_x) == YOU_LOSE);
    teardown();
}

TEST_SUITE_END();

// add tests for 
