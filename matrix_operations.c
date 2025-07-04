#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix_operations.h"


Matrix* create_matrix(int rows, int cols) {
    Matrix* mat;
    int i;

    mat = (Matrix*)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double**)malloc(rows * sizeof(double*));
    for (i = 0; i < rows; i++) {
        mat->data[i] = (double*)malloc(cols * sizeof(double));
    }
    return mat;
}

Matrix* assign_data_matrix(int rows, int cols, double** data){
    Matrix* mat;
    int j;
    int i;
    mat = create_matrix(rows,cols);       
    mat->rows = rows;
    mat->cols = cols;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            mat->data[i][j] = data[i][j];
            }
    }
    return mat;
}


Matrix* multiply_matrices(Matrix* m1, Matrix* m2) {
    Matrix* result;
    int j;
    int i ;
    int k;
    if (m1->cols != m2->rows) {
        fprintf(stderr, "An Error Has Occurred\n");
        exit(1);
    }
    result = create_matrix(m1->rows, m2->cols);
    for (i = 0; i < m1->rows; i++) {
        for (j = 0; j < m2->cols; j++) {
            result->data[i][j] = 0;
            for (k = 0; k < m1->cols; k++) {
                result->data[i][j] += m1->data[i][k] * m2->data[k][j];
            }
        }
    }
    return result;
}


Matrix* transpose_matrix(Matrix* mat) {
    int j;
    int i ;
    Matrix* result;
    result = create_matrix(mat->cols, mat->rows);
    for (i = 0; i < mat->rows; i++) {
        for (j = 0; j < mat->cols; j++) {
            result->data[j][i] = mat->data[i][j];
        }
    }
    return result;
}


Matrix* sqrt_matrix(Matrix* mat) {
    int j;
    int i;
    Matrix* result;
    result = create_matrix(mat->rows, mat->cols);
    for (i = 0; i < mat->rows; i++) {
        for (j = 0; j < mat->cols; j++) {
            result->data[i][j] = sqrt(mat->data[i][j]);
        }
    }
    return result;
}


Matrix* inverse_diagonal_matrix(Matrix* mat) {
    Matrix* result;
    int j;
    int i;
    if (mat->rows != mat->cols) {
        fprintf(stderr, "An Error Has Occurred\n");
        exit(1);
    }
    result = create_matrix(mat->rows, mat->cols);
    for (i = 0; i < mat->rows; i++) {
        for (j = 0; j < mat->cols; j++) {
            if (i == j) {
                if (mat->data[i][j] == 0) {
                    fprintf(stderr, "An Error Has Occurred\n");
                    exit(1);
                }
                result->data[i][j] = 1.0 / mat->data[i][j];
            } else {
                result->data[i][j] = 0;
            }
        }
    }
    return result;
}


void free_matrix(Matrix* mat) {
    int i;
    for (i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}


void print_matrix(Matrix* mat) {
    int j;
    int i;
    for (i = 0; i < mat->rows; i++) {
        for (j = 0; j < mat->cols; j++) {
            printf("%.4f ", mat->data[i][j]);
        }
        printf("\n");
    }
}


Matrix* add_matrices(Matrix* A, Matrix* B) {
    Matrix* result;
    int j;
    int i;
    if (A->rows != B->rows || A->cols != B->cols) {
        fprintf(stderr, "An Error Has Occurred\n");
        exit(1);
    }
    result = create_matrix(A->rows, A->cols);
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->cols; j++) {
            result->data[i][j] = A->data[i][j] + B->data[i][j];
        }
    }
    return result;
}


Matrix* subtract_matrices(Matrix* m1, Matrix* m2) {
    Matrix* result;
    int j;
    int i;

    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        fprintf(stderr, "An Error Has Occurred\n");
        exit(1);
    }
    result = create_matrix(m1->rows, m1->cols);
    for (i = 0; i < result->rows; i++) {
        for (j = 0; j < result->cols; j++) {
            result->data[i][j] = m1->data[i][j] - m2->data[i][j];
        }
    }
    return result;
}


double frobenius_norm(Matrix* mat) {
    double sum = 0.0;
    int j;
    int i;

    for (i = 0; i < mat->rows; i++) {
        for (j = 0; j < mat->cols; j++) {
            sum += mat->data[i][j] * mat->data[i][j];
        }
    }
    return sqrt(sum);
}


double squared_euclidean_distance(double* x_i, double* x_j, int d) {
    int k;
    double sum;
    double diff;

    sum = 0.0;
    for (k = 0; k < d; k++) {
        diff = x_i[k] - x_j[k];
        sum += diff * diff;
    }
    return sum;
}


