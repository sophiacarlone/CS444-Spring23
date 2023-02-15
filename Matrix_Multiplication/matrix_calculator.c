/*take two*/

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
typedef struct thread_info
{
    int *row;
    int *col;
    int id;
} thread_info;

/*functions*/
void FillMatrix(int row, int col, int (*mat)[col]);
void PrintMatrix(int row, int col, int (*mat)[col]); 
void Initialize2Zero(int (*mat)[mat2_col]);
void *Thread_Helper(void *args);
void Transpose(int row, int col, int (*mat)[col]);
int RowXColumn(int *row, int *col);
// void RowXMatrix(int *row, int (*mat)[mat2_col], int (*result)[mat2_col], int row_ID);

int main(){
//TODO: comments
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

    pthread_t threads[mat1_rows * mat2_col]; //thread array
    int status; //checks for thread status
    thread_info multiplying_threads[(mat1_rows * mat1_col)]; //created

    /*fill the matrices*/
    srand(time(0)); //Seed for random number fill
    FillMatrix(mat1_rows, mat1_col, mat1);
    FillMatrix(mat2_rows, mat2_col, mat2);
    Initialize2Zero(final_matrix);

    /*print matrices*/
    PrintMatrix(mat1_rows, mat1_col, mat1);
    PrintMatrix(mat2_rows, mat2_col, mat2);

    // thread_info multiplying_thread;
    // multiplying_thread.result=final_matrix;

    /*transpose mat2 for ease*/
    Transpose(mat2_rows, mat2_col, mat2);

    int i, row, col;
    for(i = 0; i < (mat1_rows*mat2_col); i++){
        row = i / mat2_col; //gets id of the row being used
        col = i % mat2_col; //gets id of the column to be used
        multiplying_threads[i].row=mat1[row];
        multiplying_threads[i].col=mat2[col];
        multiplying_threads[i].id=i;
        fprintf(stderr, "about to create thread\n");
        status = pthread_create(&threads[i], NULL, Thread_Helper, (void *)&multiplying_threads[i]);
        if(status)exit(1); //checking all threads are fine
    }

    //pthread_join here to wait for all to complete
    for (int i = 0; i < (mat1_rows * mat2_col); i++)
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

/*row * column computation*/
int RowXColumn(int *row, int *col){
    fprintf(stderr, "in rowxcolumn\n");

    int i, sum;
    for(i = 0; i < mat1_col; i++){
        sum += row[i] * col[i];
    }
    return sum;
}

/*for reorganizing thread data*/
void *Thread_Helper(void *args){
    int p[mat2_col];

    thread_info *data = (thread_info *)args;

    for(int i = 0; i < mat2_col; i++){
        p[i] = RowXColumn(data->row, data->col);
    }

    pthread_exit(p);
}

/*transpose matrix for ease*/
void Transpose(int row, int col, int (*mat)[col]){
    int temp[col][row];
    int i, j;
    for (i = 0; i < col; i++)
        for (j = 0; j < row; j++)
            temp[i][j] = mat[j][i];
    mat = temp;
}