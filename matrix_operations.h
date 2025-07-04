#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* 
    Represents a mathematical matrix with dynamic memory allocation for its data.
    fields:
    rows - The number of rows in the matrix.
    cols - The number of columns in the matrix.
    data - A pointer to a 2D array that stores the elements of the matrix.
*/
typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

/*
    create a Matrix struct of certain size with an empty data 2D array
    input: number of rows, number of columns
    output: Matrix pointer
*/
Matrix* create_matrix(int rows, int cols);
/*
    performs matrix multiplication if dimensions are compatible
    input: Matrix pointer, Matrix pointer
    output: Matrix pointer
*/
Matrix* multiply_matrices(Matrix* m1, Matrix* m2);
/*
    returns a new matrix that is the transpose of the input matrix.
    input: Matrix pointer
    output: Matrix pointer
*/
Matrix* transpose_matrix(Matrix* mat);
/*
    computes the element-wise square root of the given matrix.
    only non-negative elements are allowed.
    input: Matrix pointer
    output: Matrix pointer
*/
Matrix* sqrt_matrix(Matrix* mat);
/*
    calculates the inverse of a diagonal matrix.
    assumes the input matrix is square and diagonal.
    input: Matrix pointer
    output: Matrix pointer
*/
Matrix* inverse_diagonal_matrix(Matrix* mat);
/*
    frees the memory allocated for the matrix, including the data array.
    input: Matrix pointer
    output: none
*/
void free_matrix(Matrix* mat);
/*
    prints the matrix.
    input: Matrix pointer
    output: none
*/
void print_matrix(Matrix* mat);
/*
    Performs element-wise addition of two matrices with identical dimensions
    input: Matrix pointer, Matrix pointer
    output: Matrix pointer
*/
Matrix* add_matrices(Matrix* A, Matrix* B);
/*
    Performs element-wise subtraction of two matrices with identical dimensions
    input: Matrix pointer, Matrix pointer
    output: Matrix pointer
*/
Matrix* subtract_matrices(Matrix* m1, Matrix* m2);
/*
    Calculates the Frobenius norm of the given matrix, 
    defined as the square root of the sum of the squares of all elements.
    input: Matrix pointer
    output: double
*/
double frobenius_norm(Matrix* mat);
/*
    Computes the squared Euclidean distance between two vectors.
    input: pointer to a vector, pointer to a vector, vectors' dimension
    output: double
*/
double squared_euclidean_distance(double* x_i, double* x_j, int d);
/*
    Creates a matrix and assigns the provided data array to it. 
    Assumes the data array is pre-allocated and matches the specified dimensions.
    input: number of rows, number of columns, 2D array
    output: Matrix pointer
*/
Matrix* assign_data_matrix(int rows, int cols, double** data);

#endif
