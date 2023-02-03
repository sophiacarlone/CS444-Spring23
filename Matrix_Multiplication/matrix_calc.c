/*Sophia Carlone 2-19-23*/

/*All needed libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*Constants go here*/
#define RAND_UPPER_BOUND 20 /*high end for random numbers*/

/*function declarations*/
void FillMatrix(int *mat, int row, int col);
int RowXCol(int pid, int *mat1, int *mat2_col);
void PrintMatrix(int *mat, int row, int col); 

/*main function*/
int main(){
    int mat1_rows, mat1_col, mat2_rows, mat2_col;
    // intake the matrix parameters from stdin

    if(mat1_col != mat2_rows){
        //print out that you are a loser
        exit(1);
    }

    int mat1[mat1_rows][mat1_col]; /*2D arrays for matrices*/
    int mat2[mat2_rows][mat2_col];
    int final_mat[mat1_rows][mat2_col];

    /*possibility to make this threaded*/
    FillMatrix(mat1, mat1_rows, mat1_col);
    FillMatrix(mat2, mat2_rows, mat2_col);

    /*time to multiply*/
    /*
    spawn one thread per row in mat1
    each thread does it's assign row against col i of matrix 2    
    for(each thread){
        RowXCol()
        TODO: Continue pseudocode later
    }
    */

   /*print out matrixes*/
}

/*fills matrix with randomly generated numbers*/
void FillMatrix(int *mat, int row, int col){
    /*insert random numbers into the matrix
    - rand() needs a seed (can use the time)
    - place into matrix
    */
}

/*multiples a row (based on thread id) to another matrix
returns sum*/
int RowXCol(int pid, int *mat1, int *mat2_col); 

/*print matrix*/
void PrintMatrix(int *mat, int row, int col){

}