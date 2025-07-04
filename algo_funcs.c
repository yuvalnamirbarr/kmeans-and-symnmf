#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix_operations.h"
#include "algo_funcs.h"
static double EPSILON = 0.0001;


Matrix* sym(Matrix* X) {
    int N = X->rows;
    int d = X->cols;
    int i;
    int j;
    double dist;
    Matrix* A;
    
    A = create_matrix(N, N);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == j) {
                A->data[i][j] = 0.0;
            } else {
                dist = squared_euclidean_distance(X->data[i], X->data[j], d);
                A->data[i][j] = exp(-dist / 2.0);
            }
        }
    }
    return A;
}


Matrix* ddg(Matrix* A) {
    int i;
    int j;
    double sum;
    int n;
    Matrix* D;
    n = A->rows;
    D = create_matrix(n, n);
    for (i = 0; i < n; i++) {
        for(j=0; j<n; j++){
             D->data[i][j] = 0.0;
        }
    }
    for (i = 0; i < n; i++) {
        sum = 0.0;
        for (j = 0; j < n; j++) {
            sum += A->data[i][j];
        }
        D->data[i][i] = sum;
    }
    return D;
}


Matrix* norm(Matrix* A, Matrix* D) {
    Matrix* D_inv;
    Matrix* D_inv_sqrt;
    Matrix* temp; 
    Matrix* W;
    D_inv = inverse_diagonal_matrix(D);
    D_inv_sqrt = sqrt_matrix(D_inv); 
    temp = multiply_matrices(D_inv_sqrt, A);
    W = multiply_matrices(temp, D_inv_sqrt);

    free_matrix(D_inv);
    free_matrix(D_inv_sqrt);
    free_matrix(temp);

    return W;
}


Matrix* update_H(Matrix* W, Matrix* H) {
    int i;
    int j;
    double beta;
    int N;
    int k;
    Matrix* H_new;
    Matrix* WH;
    Matrix* HT;
    Matrix* HHT;
    Matrix* HHTH;

    beta = 0.5;
    N = H -> rows;
    k = H -> cols;
    H_new = create_matrix(N,k);
    WH = multiply_matrices(W,H);
    HT = transpose_matrix(H);
    HHT = multiply_matrices(H,HT);
    HHTH = multiply_matrices(HHT,H); 

    for (i = 0; i < N; i++) {
        for (j = 0; j <k ; j++) {
            H_new -> data[i][j] = (H -> data[i][j]) * ((1 - beta) + ((beta * (WH -> data[i][j])) / (HHTH -> data[i][j])));
        }
    }
    free_matrix(WH);
    free_matrix(HT);
    free_matrix(HHT);
    free_matrix(HHTH);

    return H_new;
}


Matrix* find_final_H(Matrix* W, Matrix* H) {
    
    int iter;
    double diff;
    Matrix* H_curr;
    Matrix* H_new;
    Matrix* sub;

    H_curr = H;
    iter = 0;
     
    while(iter < MAX_ITER){
        H_new = update_H(W, H_curr);
        sub = subtract_matrices(H_curr, H_new);
        diff = pow(frobenius_norm(sub), 2);

        if(H_curr != H){
                free_matrix(H_curr);
            }

        if(diff < EPSILON){ 
            return H_new;
        }
        else{
            H_curr = H_new; 
        }

        free_matrix(sub);
        iter++;
    }

    return H_curr;
}


Matrix* full_ddg(Matrix* X){
    Matrix* A = sym(X);
    Matrix* D = ddg(A);
    
    free_matrix(A);
    return D;
}


Matrix* full_norm(Matrix* X){
    Matrix* A = sym(X);
    Matrix* D = ddg(A);
    Matrix* W = norm(A,D);

    free_matrix(A);
    free_matrix(D);
    return W;
}
