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
📄 algo_funcs.c/h            # Core clustering logic (kmeans, initialization, distance)
📄 matrix_operations.c/h     # Matrix computations (norms, dot products, matrix multiplications)
📄 symnmf.c / symnmf.py      # Symmetric NMF logic in C and Python
📄 wrapper_utils.c/h         # Python-C interface helpers
📄 setup.py                  # Builds the C extension for Python
📄 analysis.py               # Main Python script to run and compare clustering results
📄 utils.py                  # Data loading, normalization, and helper functions
📄 Makefile                  # Optional C build script
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
- `<input_file>`: CSV or space-separated file of vectors (rows = data points)
- `<k>`: number of clusters

The output includes clustering results and optionally visualizations.

---

## 💡 Features

- KMeans++ implemented from scratch
- Custom SymNMF routine using iterative update rules
- Efficient memory use via NumPy + native C arrays
- Python–C integration using CPython API

---

## 🛠️ Dependencies

- Python 3.x
- NumPy
- Matplotlib (optional, for visualization)
- GCC (for compiling C code)

---

