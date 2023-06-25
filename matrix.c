#include <stdio.h>
#include <pthread.h>

#define MAX_SIZE 100

int matrixA[MAX_SIZE][MAX_SIZE], matrixB[MAX_SIZE][MAX_SIZE], matrixC[MAX_SIZE][MAX_SIZE], matrixD[MAX_SIZE][MAX_SIZE], matrixE[MAX_SIZE][MAX_SIZE], matrixF[MAX_SIZE][MAX_SIZE];
int size;

// Function to read input matrix from user
void read_matrix(int matrix[MAX_SIZE][MAX_SIZE]) {
    printf("Enter matrix of size %d x %d:\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Thread function to perform matrix addition
void *addition(void *arg) {
    printf("Matrix Addition started in thread id : %d\n", pthread_self());
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    printf("Matrix Addition completed\n");
    for(int i = 0; i < size; i++)
{
    for(int j = 0; j < size; j++)
    {
        printf("%d ", matrixC[i][j]);
    }
    printf("\n");
}
    pthread_exit(NULL);
}

// Thread function to perform matrix subtraction
void *subtraction(void *arg) {
    printf("Matrix Subtraction started in thread id : %d\n", pthread_self());
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrixE[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
    printf("Matrix Subtraction completed\n");
    for(int i = 0; i < size; i++)
{
    for(int j = 0; j < size; j++)
    {
        printf("%d ", matrixE[i][j]);
    }
    printf("\n");
}
    pthread_exit(NULL);
}

// Thread function to perform matrix multiplication
void *multiplication(void *arg) {
    printf("Matrix Multiplication started in thread id : %d\n", pthread_self());
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrixC[i][j] = 0;
            for (int k = 0; k < size; k++) {
                matrixF[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    printf("Matrix Multiplication completed\n");
    for(int i = 0; i < size; i++)
{
    for(int j = 0; j < size; j++)
    {
        printf("%d ", matrixF[i][j]);
    }
    printf("\n");
}
    pthread_exit(NULL);
}

// Thread function to compute trace of matrix
void *trace(void *arg) {
    printf("Matrix Trace started in thread id : %d\n", pthread_self());
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += matrixA[i][i];
    }
    printf("Trace of matrix = %d\n", sum);
    pthread_exit(NULL);
}

// Thread function to check AB = BA
void *check_commute(void *arg) {
    printf("Matrix Check Commute started in thread id : %d\n", pthread_self());
    int flag = 1;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrixD[i][j] = 0;
            for (int k = 0; k < size; k++) {
                matrixD[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrixC[i][j] != matrixD[i][j]) {
                flag = 0;
                break;
            }
        }
        if (flag == 0) {
            break;
        }
    }
    if (flag == 1) {
        printf("AB = BA\n");
    } else {
        printf("AB != BA\n");
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
// Get input from user
printf("Enter matrix size (up to %d): ", MAX_SIZE);
scanf("%d", &size);
read_matrix(matrixA);
read_matrix(matrixB);

// Create threads to perform matrix operations
pthread_create(&threads[0], NULL, addition, NULL);
pthread_create(&threads[1], NULL, subtraction, NULL);
pthread_create(&threads[2], NULL, multiplication, NULL);
pthread_create(&threads[3], NULL, trace, NULL);
pthread_create(&threads[4], NULL, check_commute, NULL);

// Wait for all threads to complete
for (int i = 0; i < 5; i++) {
    pthread_join(threads[i], NULL);
}

return 0;
}