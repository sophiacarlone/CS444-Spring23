/*take 3*/

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
    int *mat2;
} thread_info;

/*functions*/
void FillMatrix(int row, int col, int (*mat)[col]);
void PrintMatrix(int row, int col, int (*mat)[col]); 
void Initialize2Zero(int (*mat)[mat2_col]);
void *Thread_Helper(void *args);
int RowXColumn(int *row, int *col);

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
    for(int i = 0; i < mat2_rows; i++){
        for(int j = 0; j < mat2_col; j++){
            mat2_emulated[k] = mat2[i][j];
            k++;
        }
    }

    thread_info thread_data[mat1_rows];

    /*create threads*/
    for(int i = 0; i < mat1_rows; i++){
        thread_data[i].row = mat1[i];
        thread_data[i].mat2 = mat2_emulated;
        status = pthread_create(&threads[i], NULL, Thread_Helper, (void *)&thread_data[i]);
        if(status)exit(1);
    }

    //pthread_join here to wait for all to complete
    printf("\n testing the final matrix: ");
    for (int i = 0; i < mat1_rows; i++){
        pthread_join(threads[i], final_matrix[i]);
        for(int j = 0; j < mat2_col; j++)
            printf("%d ", final_matrix[i][j]);
    } 
    
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

void *Thread_Helper(void *args){
    int p[mat2_col];
    int placement;
    int col[mat2_rows];

    thread_info *data = (thread_info *)args;

    for(int i = 0; i < mat2_col; i++){
        placement = i * mat2_col;
        for(int j = 0; j < mat2_rows; j++){
            col[j] = data->mat2[j+placement];
        }

        // p[i] = RowXColumn(data->row, col);
        for(int k = 0; k < mat1_col; k++){
            p[i] += data->row[k] * col[k];
            printf("looking at %d * %d\n", data->row[k], col[k]);
            printf("%d \n", p[i]);
        }
        printf("\n");
    }

    printf("this row of the final result: ");
    for(int g = 0; g < mat2_col; g++)
        printf("%d ", p[g]);

    printf("\n");


    pthread_exit(*p);
}

/*row * column computation*/
int RowXColumn(int *row, int *col){

    printf("\n");
    int i, sum;
    for(i = 0; i < mat1_col; i++){
        sum += row[i] * col[i];
        printf("looking at %d * %d\n", row[i], col[i]);
    printf("%d \n", sum);

    }
    printf("%d ", sum);

    return sum;
}