/*take two*/

/*All needed libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/*Constants go here*/
#define RAND_UPPER_BOUND 20 /*high end for random numbers*/

/*Global Variables*/
int mat1_rows, mat1_col, mat2_rows, mat2_col;

//may need to create a struct here

void FillMatrix(int row, int col, int (*mat)[col]);
void PrintMatrix(int row, int col, int (*mat)[col]); 
void Initialize2Zero(int (*mat)[mat2_col]);
void RowXMatrix(int *row, int (*mat)[mat2_col], int (*result)[mat2_col], int row_ID);

int main(){
    // intake the matrix parameters from stdin
    fprintf(stdout, "please input the number of rows and columns for each matrix. Ex: r1 c1 r2 c2\n");
    scanf("%d %d %d %d", &mat1_rows, &mat1_col, &mat2_rows, &mat2_col);

    // error checking
    if(mat1_col != mat2_rows){ 
        fprintf(stdout, "the number of columns in the first matix has to be equal to the number of rows in the second matrix");
        exit(1);
    }

    int mat1[mat1_rows][mat1_col];
    int mat2[mat2_rows][mat2_col];
    int final_matrix[mat1_rows][mat2_col];

    pthread_t threads[mat1_rows]; //thread array
    int status; //checks for thread status

    srand(time(0));
    FillMatrix(mat1_rows, mat1_col, mat1);
    FillMatrix(mat2_rows, mat2_col, mat2);
    Initialize2Zero(final_matrix);

    PrintMatrix(mat1_rows, mat1_col, mat1);
    PrintMatrix(mat2_rows, mat2_col, mat2);

    int i;
    // for(i = 0; i < mat1_col; i++)
    //     RowXMatrix(mat1[i], mat2, final_matrix, i);
    
    //pthread_create here
    for(i = 0; i < mat1_rows; i++){
        status = pthread_create(&threads[i], NULL, RowXMatrix, (void *)i);
        if(status)exit(1); //checking all threads are fine
    }

    //pthread_join here to wait for all to complete
    for (int i = 0; i < mat1_rows; i++)
        pthread_join(threads[i], NULL); 
    
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

void RowXMatrix(int *row, int (*mat)[mat2_col], int (*result)[mat2_col], int row_ID){

}

int RowXColumn(int *row, int *col){
    int i, sum;
    for(i = 0; i < mat1_col; i++){
        sum += row[i] * col[i];
    }
    return sum;
}