/*
 * ParallelMatrix.c
 *
 *  Created on: 30/08/2016
 *      Author: christopher
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef double** Matrix; //Let's make my life easier
typedef struct {
	Matrix A, B, C;
	int i;
	int j;
	int n;
} MatrixData;
typedef pthread_t PThread; //It looks nicer!

Matrix matrixMultiplication(Matrix A, Matrix B, int m, int n, int l); //Regular single-threaded matrix multiplication
Matrix matrixMultiplicationParallel(Matrix A, Matrix B, int m, int n, int l, PThread*** t); //Multithreaded Matrix Multiplication
Matrix newMatrix(int m, int n); //Initializes a new matrix of doubles (double**) dynamically
void* calculateCell(void* param); //Paralelizable code function. Called by pthread_create()
MatrixData* newMatrixData(Matrix A, Matrix B, Matrix C, int i, int j, int n); //Encapsulates matrix data for calculateCell() to use it
void printMatrix(Matrix A, int m, int n); //Prints a m by n matrix to stdout


int main(void) {
	PThread*** t = (PThread***) malloc(sizeof(PThread**)); //Pointer to thread matrix

	Matrix A = newMatrix(2, 3);
	Matrix B = newMatrix(3, 2);

	A[0][0] = 2; A[0][1] = 5; A[0][2] = 3;
	A[1][0] = 4; A[1][1] = 9; A[1][2] = 6;

	B[0][0] = 3; B[0][1] = 2;
	B[1][0] = 6; B[1][1] = 3;
	B[2][0] = 7; B[2][1] = 9;

	Matrix C = matrixMultiplicationParallel(A, B, 2, 3, 2, t);
	printMatrix(C, 2, 2);

	free(t); //Avoiding memory leaks since 1989

	return 0;
}

Matrix matrixMultiplication(Matrix A, Matrix B, int m, int n, int l) {
	Matrix C = newMatrix(m, l);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < l; j++) {
			C[i][j] = 0;
			for (int k = 0; k < n; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}

Matrix matrixMultiplicationParallel(Matrix A, Matrix B, int m, int n, int l, PThread*** t) {
	(*t) = (PThread**) calloc(m, sizeof(PThread*));
	for (int i = 0; i < m; i++) {
		(*t)[i] = (PThread*) calloc(l, sizeof(PThread));
	}
	Matrix C = newMatrix(m, l);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < l; j++) { //Substitute inner for by the pthread
			pthread_create(&((*t)[i][j]), //Pointer magic, dereference t to get a PThread*,then access matrix-like, after take the address of the PThread variable-
						   NULL,
						   calculateCell, //Function pointer
						   (void*) newMatrixData(A,B,C,i,j,n) //Create MatrixData* and cast to void*
			);
		}
	}
	for (int i = 0; i < m; i++) { //Walk through the matrix and sync all threads to main thread
		for (int j = 0; j < l; j++) {
			pthread_join((*t)[i][j], NULL);
		}
	}
	return C; //Return the resultant matrix after all threads have finished
}

Matrix newMatrix(int m, int n) {
	Matrix A = (Matrix) calloc(m, sizeof(double*));
	for (int i = 0; i < m; i++) {
		A[i] = (double*) calloc(n, sizeof(double));
	}
	return A;
}

MatrixData* newMatrixData(Matrix A, Matrix B, Matrix C, int i, int j, int n) { //Uses the MatrixData struct to encapsulate everything
	MatrixData* data = malloc(sizeof(MatrixData));
	data->A = A;
	data->B = B;
	data->C = C;
	data->i = i;
	data->j = j;
	data->n = n;
	return data;
}

void* calculateCell(void* param) { //Same inner for, but using MatrixData to access the elements
	MatrixData* data = (MatrixData*) param;
	data->C[data->i][data->j] = 0;
	for (int k = 0; k < data->n; k++) {
		data->C[data->i][data->j] += data->A[data->i][k] * data->B[k][data->j];
	}
	free(data); //Be nice, free your memory :)
	pthread_exit(NULL);
}

void printMatrix(Matrix A, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%i ", (int) A[i][j]);
		}
		printf("\n");
	}
}
