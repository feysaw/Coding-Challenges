#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

int32_t width = 0;
int32_t height = 0;

void generate_game_board(uint8_t** game_board) {
    srand(time(0));
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            game_board[y][x] = rand() % 2;
        }
    }
}

void evolve_game_board(uint8_t** game_board) {
    uint8_t new[height][width];
    printf("Evolving the game board...\r\n");
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            int32_t n = 0;
            
            for (int32_t y1 = y - 1; y1 <= y + 1; y1++) {
                for (int32_t x1 = x - 1; x1 <= x + 1; x1++) {
                    if (y1 < 0 || x1 < 0 || y1 == height || x1 == width || (y1 == y && x1 == x)) {
                        continue;
                    }
                    
                    if (game_board[y1][x1]) {
                        n++;
                    }
                }
            }
            
            new[y][x] = ((n == 2 && game_board[y][x]) || n == 3);
        }
    }
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            game_board[y][x] = new[y][x];
        }
    }
}

void print_game_board(uint8_t** game_board) {
    for (int32_t i = 0; i < height; i++) {
        printf("  ");
        
        for (int32_t ii = 0; ii < width; ii++) {
            printf(game_board[i][ii] == 0 ? "-" : "x");
        }
        
        printf("\r\n");
    }
}

uint8_t check_end_of_game(uint8_t** game_board) {
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            if (game_board[y][x]) {
                return 0;
            }
        }
    }
    
    return 1;
}

int run_game(void) {
    printf("| Generating this initial game board:                                   |\r\n"
           "+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+\r\n");
    uint8_t** game_board = (uint8_t**) malloc(sizeof(uint8_t*) * height);
    
    for (int32_t i = 0; i < height; i++) {
        game_board[i] = (uint8_t*) malloc(sizeof(uint8_t) * width);
    }
    
    generate_game_board(game_board);
    printf("\r\n");
    print_game_board(game_board);
    printf("\r\nPress 'Enter' to begin...");
    while (getchar() != 10);
    
    while (1) {
        printf("\r\n");
        evolve_game_board(game_board);
        printf("After evolution, the current game board looks like:\r\n\r\n");
        print_game_board(game_board);
        
        if (check_end_of_game(game_board)) {
            printf("\r\nThere are no further generations. All cells are extinct!");
        } else {
            sleep(5);
        }
    }
    
    for (int32_t i = 0; i < height; i++) {
        free(game_board[i]);
    }
    
    free(game_board);
    return 0;
}

int main(int argc, char **argv) {
    if (argc <= 2) {
        printf("You must provide the width and height values for the game board.\r\n");
        return 0;
    }
    
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    
    if (width <= 0) {
        width = 40;
    }
    
    if (height <= 0) {
        height = 40;
    }
    
    printf("+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+\r\n"
           "| Welcome to Conway's Game of Life (in C)                               |\r\n"
           "|                                                                       |\r\n"
           "| Each cell of the gameboard can be one of two states, alive or dead.   |\r\n"
           "| These states are represented in output by x and -, respectively.      |\r\n"
           "| Every cell interacts with it's eight neighbors, transitioning         |\r\n"
           "| according to a set of rules.                                          |\r\n"
           "|                                                                       |\r\n"
           "| The rules are simple:                                                 |\r\n"
           "|   1. Any live cell with fewer than two living neighbors dies from     |\r\n"
           "|      underpopulation.                                                 |\r\n"
           "|   2. Any live cell with two or three living neighbors lives on to the |\r\n"
           "|      next evolution.                                                  |\r\n"
           "|   3. Any live cell with more than three living neighbors dies from    |\r\n"
           "|      overpopulation.                                                  |\r\n"
           "|   4. Any dead cell with exactly three living neighbors becomes a      |\r\n"
           "|      living cell via population.                                      |\r\n"
           "|                                                                       |\r\n"
           "| The parameters of the game board are:                                 |\r\n"
           "|   Width: %d       Height: %d                                          |\r\n"
           "|                                                                       |\r\n",
           width, height);
    return run_game();
}