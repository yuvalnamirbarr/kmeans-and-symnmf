import sys
import numpy as np
from utils import *
import symnmf_mod

np.random.seed(1234)

def init_H(W_norm_matrix, n, k_clusters):
    entries_average_m = np.mean(W_norm_matrix)
    upper_bound = 2 * np.sqrt(entries_average_m / k_clusters)
    H_shape = (n, k_clusters)
    return np.random.uniform(0, upper_bound, H_shape).tolist()

def calc_matrix_caller(mat, k_clust, n_data_points, goal):
    if goal == 'symnmf':
        w_norm = symnmf_mod.norm(mat)  # c function
        h_init = init_H(w_norm, n_data_points, k_clust)  # python function
        return symnmf_mod.symnmf(h_init, w_norm)  # c function H

    elif goal == 'sym':
        return symnmf_mod.sym(mat)  # c function A
    elif goal == 'ddg':
        return symnmf_mod.ddg(mat)  # c function D
    elif goal == 'norm':
        return symnmf_mod.norm(mat)  # c function W


if __name__ == "__main__":
    #################### GET INPUTS ########################

    k_clusters = int(sys.argv[1])
    goal = str(sys.argv[2])
    file_name = sys.argv[3]

    file_input_matrix = read_input_file(file_name)
    n_points = file_input_matrix.shape[0]
    
    if k_clusters >= n_points:
        print("An Error Has Occurred" )
        sys.exit(1)

    #################### EXECUTE GOAL ###########################
    matrix_as_list = file_input_matrix.tolist()
    out_matrix = calc_matrix_caller(matrix_as_list, k_clusters, n_points, goal)
    print_matrix(out_matrix)

    
    

