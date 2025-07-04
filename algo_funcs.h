#ifndef MATRIX_ALGEBRA_H
#define MATRIX_ALGEBRA_H

#include "matrix_operations.h"

#define MAX_ITER 300

/*  compute similarity matrix A from matrix X
    input: Matrix (size Nd) pointer
    output: Matrix (size NN) pointer
*/
Matrix* sym(Matrix* X);
/*  compute diagonal degree matrix D from matrix A
    input: Matrix (size N*N) pointer
    output: Matrix (size N*N) pointer
*/
Matrix* ddg(Matrix* A);
/*  compute normalized similarity matrix W from matrices A, D
    input: Matrix (size N*N) pointer, Matrix (size NN) pointer
    output: Matrix (size N*N) pointer
*/
Matrix* norm(Matrix* A, Matrix* D);
/*  compute H(t+1), given W and H(t) by rule 1.4.2
    input: Matrix (size N*N) pointer, Matrix (size Nk) pointer
    output: Matrix (size N*k) pointer
*/
Matrix* update_H(Matrix* W, Matrix* H);
/*  compute final association matrix H
    input: Matrix (size N*N) pointer, Matrix (size Nk) pointer
    output: Matrix (size N*k) pointer
*/
Matrix* find_final_H(Matrix* W, Matrix* H);
/*  compute diagonal degree matrix D from matrix X
    input: Matrix (size N*N) pointer
    output: Matrix (size N*N) pointer
*/
Matrix* full_ddg(Matrix* X);
/*  compute normalized similarity matrix W from matrix X
    input: Matrix (size N*N) pointer
    output: Matrix (size N*N) pointer
*/
Matrix* full_norm(Matrix* X);


#endif