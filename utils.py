import numpy as np
import sys

def read_input_file(file_name):
    try:
        data = np.loadtxt(file_name, delimiter=",")
        if data.ndim ==1:
            data = data.reshape(-1,1)
        return data
    except Exception as e:
        print("An Error Has Occurred\n")
        sys.exit(1)

def print_matrix(matrix):
    for row in matrix:
        print(",".join(f"{val: .4f}" for val in row))

