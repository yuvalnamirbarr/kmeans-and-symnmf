import sys
import math

def read_data(file_path):
    data = []
    try:
        with open(file_path, 'r') as f:
            for line in f:
                line = line.strip().split()
                point_str = line[0].split(',')
                point_flt = [float(x) for x in point_str]
                data.append(point_flt)
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return None
    return data


def check_data(data_points, k, iter= 300):
    N = len(data_points)
    assert N > k, 'Invalid number of data points!'
    assert k > 1, 'Invalid number of clusters!'
    assert 1 < iter < 1000, 'Invalid number of iterations!'

def euclidean_distance(point1, point2):
    return math.sqrt(sum([(point1[i] - point2[i]) ** 2 for i in range(len(point1))]))

def init_centers(data_points, k):
    miu_centers = data_points[:k]
    return miu_centers

def allocate_data(data_points, miu_centers):
    groups = [[] for _ in range(len(miu_centers))]
    dim_data = len(data_points[0])
    labels = []

    for point in data_points:
        min_distance = math.inf
        min_index = 0
        for i, center in enumerate(miu_centers):
            distance = euclidean_distance(point, center)
            if distance < min_distance:
                min_distance = distance
                min_index = i

        groups[min_index].append(point)
        labels.append(min_index)

    curr_miu = []
    for group in groups:
        miu = [0 for _ in range(dim_data)]
        for point in group:
            for i in range(dim_data):
                miu[i] += point[i]

        miu = [x / len(group) for x in miu]
        curr_miu.append(miu)

    diff_miu = [euclidean_distance(curr_miu[i], miu_centers[i])for i in range(len(miu_centers))]
    max_diff = max(diff_miu)
    return curr_miu, max_diff, labels



def kmeans(k, data_path, iteration=300):
    max_diff = math.inf
    data = read_data(data_path)
    check_data(data, k, iteration)
    miu_centers = init_centers(data, k)
    epsilon = 4e-1

    curr_iter = 1
    while max_diff >= epsilon or curr_iter < iteration:
        miu_centers, max_diff, labels = allocate_data(data, miu_centers)
        curr_iter += 1

    return miu_centers, labels

def print_centers(centers):
    for center in centers:
        print(','.join([f'{x:.4f}' for x in center]))


if __name__ =='__main__':
    centers = []
    if len(sys.argv) == 3:
        centers, labels = kmeans(int(sys.argv[1]), sys.argv[2])
    elif len(sys.argv) == 4:
        centers, labels = kmeans(int(sys.argv[1]), sys.argv[3], int(sys.argv[2]))
    print_centers(centers)


