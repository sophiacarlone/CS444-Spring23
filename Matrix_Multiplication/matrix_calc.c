/*Sophia Carlone 2-19-23*/

/*All needed libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/*Constants go here*/
#define RAND_UPPER_BOUND 20 /*high end for random numbers*/

/*Global Variables*/
int mat1_rows, mat1_col, mat2_rows, mat2_col; //I try not to make global variables, but this was easier

//TODO: use these variables to advantage

/*function declarations*/
void FillMatrix(int row, int col, int (*mat)[col]);
// int RowXCol(int *row, int *col, int size);
void PrintMatrix(int row, int col, int (*mat)[col]); 
// int *IsolateColumn(int (*matrix)[mat2_col], int n);
void RowXMatrix(int *row, int (*mat)[mat2_col], int (*result)[mat2_col], int row_ID);
void Initialize2Zero(int (*mat)[mat2_col]);

/*main function*/
int main(){
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

    Initialize2Zero(final_mat);
    PrintMatrix(mat1_rows, mat2_col, final_mat);

 //   int temp_col[mat2_rows]; /*see if you can avoid this later (IDEA: make the RowXCol return an array)*/

    /*possibility to make this threaded*/
    srand(time(0));
    FillMatrix(mat1_rows, mat1_col, mat1);
    FillMatrix(mat2_rows, mat2_col, mat2);
    
    PrintMatrix(mat1_rows, mat1_col, mat1);
    PrintMatrix(mat2_rows, mat2_col, mat2);

    /*matrix multiplication*/
    int i, j;
    for(i = 0; i < mat1_rows; i++){
        // RowXMatrix(mat1[i], mat2, final_mat[i]); //Continue here
        for(j = 0; j < mat1_col; j++){
            printf("%d\n", final_mat[i][j]);
        }
    }   

    PrintMatrix(mat1_rows, mat2_col, final_mat);
}

/*fills matrix with randomly generated numbers*/
/*? solidfy understanding of int **mat */
// int RowXCol(int *row, int *col, int size);
void FillMatrix(int row, int col, int (*mat)[col]){ /*Something learned: passing 2d arrays take **m */
    int i;
    int j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            mat[i][j] = (rand() % RAND_UPPER_BOUND);
            // fprintf(stdout, "%d, ", mat[i][j]);
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

void RowXMatrix(int *row, int (*mat)[mat2_col], int (*result)[mat2_col], int row_ID){
    int j, k;
    for(j = 0; j < mat2_col; j++){
        for(k = 0; k < mat1_col; k++)
            result[row_ID][j] += row[k] * mat[k][j];
    }
}

void Initialize2Zero(int (*mat)[mat2_col]){
    int i, j;
    for(i = 0; i < mat1_rows; i++){
        for(j = 0; j < mat2_col; j++)
            mat[i][j] = 0;
    }
}

/*Unused Functions*/

/*Used to isolate a column from a matrix*/
int *IsolateColumn(int (*matrix)[mat2_col], int n){
    int i;
    int *result = malloc(mat2_rows);
    for(i = 0; i < mat2_rows; i++){
        result[i] = matrix[i][n];
    }
    int j;
    for(j = 0; j < mat2_rows; j++) printf("\n%d, ", result[j]);
    return result;
}

/*multiples a row to column. Returns sum*/
int RowXCol(int *row, int *col, int size){
    int i;
    int sum = 0; /*can later add in fold (if you want to practice that)*/
    for(i = 0; i < size; i++)
        sum += row[i] * col[i];
    return sum;
}
