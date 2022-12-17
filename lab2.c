#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "lab2.h"

void *row_validate(void* param);
void *grid_validate(void* param);
void *column_validate(void* param);


int** read_board_from_file(char* filename){
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    int** sudoku_board = (int**)malloc(sizeof(int*)*ROW_SIZE);
    for(int row = 0; row < ROW_SIZE; row++){
	sudoku_board[row] = (int*)malloc(sizeof(int)*COL_SIZE);

    for(int i=0; i < ROW_SIZE; i++){
        for(int j =0; j< COL_SIZE; j++){
            fscanf(fp, "%d", &sudoku_board[i][j]);
        }
    }
    fclose(fp);
    return sudoku_board;
}

    // replace this comment with y
}


int is_board_valid(){
    /* the thread identifiers */
    pthread_t* tid=
    (pthread_t*)malloc(sizeof(int)*NUM_OF_THREADS);
    param_struct* params = (param_struct*)malloc(sizeof(param_struct)*NUM_OF_THREADS);
    pthread_attr_t attr;

    int thread_index=0;
    int i,j;
    for (i = 0;i<9;i++){
        for(j=0;j<9;j++){
            //grid
            if(i%3 == 0 && j%3 == 0){
                // id of thread and parameters
                params[thread_index].id = thread_index;
                params[thread_index].starting_row = i;
                params[thread_index].starting_col = j;
                params[thread_index].ending_row = i+2;
                params[thread_index].ending_col = j+2;
                // create unique thread
                pthread_create(&(tid[thread_index++]), &attr, grid_validate, &(params[thread_index++]));
            }
            //column
            if(i==0){
                params[thread_index].id = thread_index; // id
                params[thread_index].starting_row = i;
                params[thread_index].starting_col = j;
                params[thread_index].ending_row = i;
                params[thread_index].ending_col = j+8;
                pthread_create(&(tid[thread_index++]), &attr, column_validate, &(params[thread_index++]));
            }
            //row
            if(j==0){
                params[thread_index].id = thread_index; // id
                params[thread_index].starting_row = i;
                params[thread_index].starting_col = j;
                params[thread_index].ending_row = i+8;
                params[thread_index].ending_col = j;
                pthread_create(&(tid[thread_index++]), &attr, row_validate, &(params[thread_index++]));
            }
        }
    }
    // let threads finish
    for(i=0;i<NUM_OF_THREADS;i++){
        pthread_join(tid[i],NULL);

    }
    // invalid if worker_validation at i equals 0
    for(i=0;i<NUM_OF_THREADS;i++){
        if(worker_validation[i]==0){
            printf("invalid\n");
            return EXIT_SUCCESS;
        }
    }
    printf("Solution is valid\n");
    return EXIT_SUCCESS;
    
    // replace this comment with your code
    
}

void *row_validate(void* param){
    param_struct *params = (param_struct*) param;
    int id = params->id;
    int row = params->starting_row;
    int col = params->starting_col;
    int row_end = params->ending_row;
    int col_end = params->ending_col;

    //checks 1-9 in row here
    int valid_arr[9]={0};
    int i;
    for(i=0; i<9;i++){
        //thread will exit if number is encountered again
        int num = sudoku_board[row][i];
        if(num <1 || 9<num || valid_arr[num-1]==1){
            pthread_exit(NULL);
        }

        //number doesnt repeat so it is valid
        else{
            valid_arr[num-1]=1;
        }
    }
    //validate thread
    worker_validation[id]==1;
    pthread_exit(NULL);
}
void *column_validate(void* param){
    param_struct *params = (param_struct*) param;
    int id = params->id;
    int row = params->starting_row;
    int col = params->starting_col;
    int row_end = params->ending_row;
    int col_end = params->ending_col;

    //checks 1-9 in column here
    int valid_arr[9]={0};
    int i;
    for(i=0; i<9;i++){
        //thread will exit if number is encountered again
        int num = sudoku_board[i][col];
        if(num <1 || 9<num || valid_arr[num-1]==1){
            pthread_exit(NULL);
        }

        //number doesnt repeat so it is valid
        else{
            valid_arr[num-1]=1;
        }
    }
    //validate thread
    worker_validation[id]==1;
    pthread_exit(NULL);
}
void *grid_validate(void* param){
    param_struct *params = (param_struct*) param;
    int id = params->id;
    int row = params->starting_row;
    int col = params->starting_col;
    int row_end = params->ending_row;
    int col_end = params->ending_col;

    //checks 1-9 in grid here
    int valid_arr[9]={0};
    int i,j;
    for(i=row; i<row+3;i++){
        for(j=col; j<col+3;j++){
            //thread will exit if number is encountered again
            int num = sudoku_board[i][j];
            if(num <1 || 9<num || valid_arr[num-1]==1){
                pthread_exit(NULL);
            }

            //number doesnt repeat so it is valid
            else{
                valid_arr[num-1]=1;
            }
        }
    }
    //validate thread
    worker_validation[id]==1;
    pthread_exit(NULL);
}
