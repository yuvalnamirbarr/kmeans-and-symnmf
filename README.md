# 📊 KMeans++ and Symmetric NMF Clustering

This project implements unsupervised clustering algorithms from scratch, using a combination of C for performance and Python for usability. It includes both the classic **KMeans++** algorithm and a spectral clustering variant based on **Symmetric Non-negative Matrix Factorization (SymNMF)**.

---

## 🧠 Project Overview

- **KMeans++**: Initializes centroids with better separation than random choice, improving convergence.
- **SymNMF**: Applies spectral clustering via matrix decomposition on the symmetric normalized Laplacian.
- All core numerical computations are implemented in **C** and exposed to Python via C extensions (`setup.py`).

---

## 📁 Repository Structure

```
📄 algo_funcs.c/h            # KMeans++ logic: initialization, distance calculation, centroid updates
📄 matrix_operations.c/h     # Low-level matrix operations: dot product, norms, multiplication
📄 symnmf.c                  # SymNMF core algorithm implemented in C
📄 symnmf.py                 # Python wrapper to call SymNMF logic
📄 symmodule.c               # CPython extension interface between Python and C
📄 wrapper_utils.c/h         # Utility functions for data conversion and memory handling in the interface layer
📄 kmean.py                  # Python interface for KMeans algorithm
📄 analysis.py               # Main script to run experiments using KMeans and SymNMF
📄 utils.py                  # Helpers: reading input, preprocessing, data conversion
📄 setup.py                  # Builds the C extension module for Python
📄 Makefile                  # Optional build script for pure-C compilation
```

---

## ⚙️ Installation & Build

To build the C extension and prepare the Python module:

```bash
python3 setup.py build_ext --inplace
```

Alternatively, for C-only testing:
```bash
make
```

---

## ▶️ Running the Clustering

To run the full pipeline (from Python):
```bash
python3 analysis.py <input_file> <k>
```
- `<input_file>`: Space-separated file of vectors (rows = data points)
- `<k>`: number of clusters

The output includes clustering results printed to standard output.

---

## 💡 Features

- Custom implementation of KMeans++
- Spectral clustering via SymNMF using iterative update rules
- Efficient computation via C back-end
- Integrated Python–C interface using CPython API

---

## 🛠️ Dependencies

- Python 3.x
- NumPy
- GCC (for compiling C code)

---
