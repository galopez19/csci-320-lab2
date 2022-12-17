#include <stdio.h>
#include <stdlib.h>
#include "lab2.h"

int main(int argc, char *argv[]){
    
    
    if (argc < 2){
        fprintf(stderr,"SYNOPSIS: %s <file name>\n",argv[0]);
        return 1;
    }

    sudoku_board = read_board_from_file(argv[1]);
    
    if (sudoku_board == NULL){
        fprintf(stderr,"No board available to validate. File %s is empty or unreadable.\n",argv[1]);
        return 2;
    }
    
    if (is_board_valid()){
        printf("The board is valid.\n");
    } else {
        printf("The board is not valid.\n");
    }
    
    for(int row = 0; row < ROW_SIZE; row++){
        free(sudoku_board[row]);
    }
    free(sudoku_board);
    return 0;
}