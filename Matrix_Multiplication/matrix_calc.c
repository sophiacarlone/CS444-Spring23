/*Sophia Carlone 2-19-23*/

/*All needed libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/*Constants go here*/
#define RAND_UPPER_BOUND 20 /*high end for random numbers*/

/*function declarations*/
void FillMatrix(int row, int col, int (*mat)[col]);
int RowXCol(int *row, int *col, int size);
void PrintMatrix(int row, int col, int (*mat)[col]); 

/*main function*/
int main(){
    int mat1_rows, mat1_col, mat2_rows, mat2_col;

    // intake the matrix parameters from stdin
    fprintf(stdout, "please input the number of rows and columns for each matrix. Ex: r1 c1 r2 c2\n");
    scanf("%d %d %d %d", &mat1_rows, &mat1_col, &mat2_rows, &mat2_col);

    // error checking
    if(mat1_col != mat2_rows){ 
        fprintf(stdout, "the number of columns in the first matix has to be equal to the number of rows in the second matrix");
        exit(1);
    }

    /*2D arrays for matrices*/
    int mat1[mat1_rows][mat1_col]; 
    int mat2[mat2_rows][mat2_col];
    int final_mat[mat1_rows][mat2_col];

    /*possibility to make this threaded*/
    FillMatrix(mat1_rows, mat1_col, mat1);
    FillMatrix(mat2_rows, mat2_col, mat2);
    
    PrintMatrix(mat1_rows, mat1_col, mat1);
    PrintMatrix(mat2_rows, mat2_col, mat2);
}

/*fills matrix with randomly generated numbers*/
/*? solidfy understanding of int **mat */
void FillMatrix(int row, int col, int (*mat)[col]){ /*Something learned: passing 2d arrays take **m */
    srand(time(NULL));
    int i;
    int j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            mat[i][j] = (rand() % RAND_UPPER_BOUND);
            fprintf(stdout, "%d, ", mat[i][j]);
        }
    }
}

/*print matrix*/
/*TODO: learn how to pass the 2d matrix by reference*/
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

/*multiples a row (based on thread id) to another matrix
returns sum*/
int RowXCol(int *row, int *col, int size){
    int i;
    int sum = 0; /*can later add in fold (if you want to practice that)*/
    for(int i = 0; i < size; i++)
        sum += row[i] * col[i];
    return sum;
}
