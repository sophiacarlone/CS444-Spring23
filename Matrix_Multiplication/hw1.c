// Operating Systems - CS444/544
// Spring 2023
// Sophia Carlone
// Matrix Multiplication with Multithreading
// Using pthreads, matrix multiplication in which the size of the initial 
// matrixes are determined by user input and then filled with random number is parallelized
// 2/14/2023
// https://youtu.be/PYfOkKIpCN8

/*All needed libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/*Constants*/
#define RAND_UPPER_BOUND 20 /*high end for random numbers*/

/*Global Variables*/
int mat1_rows, mat1_col, mat2_rows, mat2_col;

//Created types
typedef struct thread_info{
    int *row; //row to multiply
    int *mat2; //entire matrix emulated in a 1d array
    int *resulting_row; //row in final matrix the thread is figuring out
} thread_info;

/*functions*/
void FillMatrix(int row, int col, int (*mat)[col]);
void PrintMatrix(int row, int col, int (*mat)[col]); 
void Initialize2Zero(int (*mat)[mat2_col]);
void *Thread_Helper(void *args);

int main(){
//TODO: Malloc
//TODO: Assert

    // intake the matrix parameters from stdin
    fprintf(stdout, "please input the number of rows and columns for each matrix. Ex: r1 c1 r2 c2\n");
    scanf("%d %d %d %d", &mat1_rows, &mat1_col, &mat2_rows, &mat2_col);

    // error checking
    if(mat1_col != mat2_rows){ 
        fprintf(stdout, "the number of columns in the first matix has to be equal to the number of rows in the second matrix");
        exit(1);
    }

    /*creating matrices*/
    int mat1[mat1_rows][mat1_col];
    int mat2[mat2_rows][mat2_col];
    int final_matrix[mat1_rows][mat2_col];

    pthread_t threads[mat1_rows]; //thread array
    int status; //checks for thread status

    /*fill the matrices*/
    srand(time(0)); //Seed for random number fill
    FillMatrix(mat1_rows, mat1_col, mat1);
    FillMatrix(mat2_rows, mat2_col, mat2);
    Initialize2Zero(final_matrix);

    /*print matrices*/
    PrintMatrix(mat1_rows, mat1_col, mat1);
    PrintMatrix(mat2_rows, mat2_col, mat2);

    /*place matrix 2 into a 1d array for ease*/
    int mat2_emulated[mat2_rows*mat2_col];
    int k = 0;
    for(int i = 0; i < mat2_col; i++){
        for(int j = 0; j < mat2_rows; j++){
            mat2_emulated[k] = mat2[j][i];
            k++;
        }
    }

    /*created the structures for the thread info to be passed*/
    thread_info thread_data[mat1_rows];

    /*create threads*/
    for(int i = 0; i < mat1_rows; i++){
        thread_data[i].row = mat1[i]; /*row to be multiplied in the string*/
        thread_data[i].mat2 = mat2_emulated; /*entire matrix used for computations*/
        thread_data[i].resulting_row = final_matrix[i]; /*What row of the final matrix the thread is computing*/
        status = pthread_create(&threads[i], NULL, Thread_Helper, (void *)&thread_data[i]);
        if(status)exit(1);
    }

    /*join together*/
    for (int i = 0; i < mat1_rows; i++)
        pthread_join(threads[i], NULL);

    /*Print final result*/    
    PrintMatrix(mat1_rows, mat2_col, final_matrix);
}

/*Fill Matrix with random numbers*/
void FillMatrix(int row, int col, int (*mat)[col]){ /*Something learned: passing 2d arrays take **m */
    int i;
    int j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            mat[i][j] = (rand() % RAND_UPPER_BOUND);
        }
    }
}

/*print matrix*/
void PrintMatrix(int row, int col, int (*mat)[col]){
    printf("\nnew matrix\n");
    int i;
    int j;
    for(i = 0; i < row; i++){
        printf("row: \n");
        for(j = 0; j < col; j++){
            printf("%d, ", mat[i][j]);
        }
        printf("\n");
    }
}

/*initialize result matrix to zero*/
void Initialize2Zero(int (*mat)[mat2_col]){
    int i, j;
    for(i = 0; i < mat1_rows; i++){
        for(j = 0; j < mat2_col; j++)
            mat[i][j] = 0;
    }
}

/*Thread function to find answers for respective result matrix row*/
void *Thread_Helper(void *args){
    int placement; /*for keeping track of which column being used*/
    int col[mat2_rows]; /*array that holds column used at one time*/

    thread_info *data = (thread_info *)args; /*taking the data from the structure out of the argument*/

    /*computations*/
    for(int i = 0; i < mat2_col; i++){
        /*for getting the correct column*/
        placement = i * mat2_rows; /*which column are we on (start of the id array)*/
        for(int j = 0; j < mat2_rows; j++){
            col[j] = data->mat2[j+placement];
        }
        /*the good stuff*/
        for(int k = 0; k < mat1_col; k++){
            data->resulting_row[i] += data->row[k] * col[k]; /*cell * cell*/
        }
    }
}
