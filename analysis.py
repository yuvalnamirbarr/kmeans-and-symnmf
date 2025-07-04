import sys
import numpy as np
from sklearn.metrics import silhouette_score
from utils import read_input_file
import kmean
import symnmf

def run_kmeans(k, file_name):
    centers, labels = kmean.kmeans(k, file_name)
    return labels

def run_symnmf(data, k):
    N = data.shape[0]
    data = data.tolist()
    H = symnmf.calc_matrix_caller(data, k, N, 'symnmf')
    labels = np.argmax(H, axis=1)
    return labels

def calculate_silhouette(data, labels):
    try:
        score = silhouette_score(data, labels)
        return score
    except ValueError as e:
        print("An Error Has Occurred\n")
        sys.exit(1)

def main():
    k = int(sys.argv[1])
    file_name = sys.argv[2]
    data = read_input_file(file_name)    

    # calc silhouette_nmf
    symnmf_labels = run_symnmf(data, k)
    silhouette_nmf = calculate_silhouette(data,symnmf_labels)
    print(f"nmf: {silhouette_nmf:.4f}")

    # silhouette_kmeans
    kmeans_labels = run_kmeans(k, file_name)
    silhouette_kmeans = calculate_silhouette(data, kmeans_labels)
    print(f"kmeans: {silhouette_kmeans:.4f}")

    
if __name__ == "__main__":
    main()
