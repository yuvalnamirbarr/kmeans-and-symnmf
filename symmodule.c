# define PY_SSIZE_T_CLEAN
# include <Python.h>

# include "matrix_operations.h"
# include "algo_funcs.h"
# include "wrapper_utils.h"


static PyObject* symnmf_w(PyObject *self, PyObject *args) {
    PyObject* H_py;
    PyObject* W_py;
    PyObject* H_result_py;
    int N;
    int k;
    double** H_data;
    double** W_data;
    Matrix* W;
    Matrix* H_init;
    Matrix* H;

    if(!PyArg_ParseTuple(args, "OO", &H_py, &W_py)){
        return NULL;
    }

    N = get_num_rows(H_py);
    k = get_num_cols(H_py);
    H_data = copy_pyobject_to_carray(H_py, N, k);
    W_data = copy_pyobject_to_carray(W_py, N, N);
    H_init = assign_data_matrix(N, k, H_data);
    W = assign_data_matrix(N, N, W_data);
    H = find_final_H(W,H_init);
    H_result_py = carray_to_pylist(H->data, N, k);
    free_carray(H_data, N);
    free_carray(W_data, N);
    free_matrix(H_init);
    free_matrix(W);
    free_matrix(H);

    return H_result_py;
}

static PyObject* sym_w(PyObject *self, PyObject *args) {
    PyObject* data;
    PyObject* A_result_py;
    int N;
    int d;
    double** data_points;
    Matrix* X;
    Matrix* A;

    if(!PyArg_ParseTuple(args, "O", &data)){
        return NULL;
    }
    
    N = get_num_rows(data);
    d = get_num_cols(data);
    
    data_points = copy_pyobject_to_carray(data, N, d);
    X = assign_data_matrix(N, d, data_points);
    A = sym(X);


    A_result_py = carray_to_pylist(A->data, N, N);
    free_carray(data_points, N);
    free_matrix(X);
    free_matrix(A);
    
    return A_result_py;
}

static PyObject* ddg_w(PyObject *self, PyObject *args) {
    PyObject *data;
    PyObject *D_result_py;
    int N;
    int d;
    Matrix* D;
    Matrix* X;
    double** data_points;
    

    if(!PyArg_ParseTuple(args, "O", &data)){
        return NULL;
    }

    N = get_num_rows(data);
    d = get_num_cols(data);
    data_points = copy_pyobject_to_carray(data, N, d);

    X = assign_data_matrix(N, d, data_points);
    D = full_ddg(X);

    D_result_py = carray_to_pylist(D->data, N, N);
    free_carray(data_points, N);
    free_matrix(X);
    free_matrix(D);
    
    return D_result_py;
}

static PyObject* norm_w(PyObject *self, PyObject *args) {
    PyObject *data;
    PyObject *W_result_py;
    int N;
    int d;
    double** data_points;
    Matrix* X;
    Matrix* W;

    if(!PyArg_ParseTuple(args, "O", &data)){
        return NULL;
    }

    N = get_num_rows(data);
    d = get_num_cols(data);

    data_points = copy_pyobject_to_carray(data, N, d);
    X = assign_data_matrix(N, d, data_points);
    W = full_norm(X);
    W_result_py = carray_to_pylist(W->data, N, N);

    free_carray(data_points, N);
    free_matrix(X);
    free_matrix(W);
    return W_result_py;
}

static PyMethodDef symnmf_FunctionsTable[] = {
    {
        "symnmf", // name exposed to Python
        symnmf_w, // C wrapper function
        METH_VARARGS, // received variable args (but really just 1)
        "get the final H" // documentation
    }, {
        "sym", // name exposed to Python
        sym_w, // C wrapper function
        METH_VARARGS, // received variable args (but really just 1)
        "get similarity matrix A" // documentation
    }, {
        "ddg", // name exposed to Python
        ddg_w, // C wrapper function
        METH_VARARGS, // received variable args (but really just 1)
        "get diagonal degree matrix D" // documentation
    }, {
        "norm", // name exposed to Python
        norm_w, // C wrapper function
        METH_VARARGS, // received variable args (but really just 1)
        "get normalized similarity matrix W" // documentation
    }, {
        NULL, NULL, 0, NULL
    }
};

static struct PyModuleDef symnmf_Module = {
    PyModuleDef_HEAD_INIT,
    "symnmf_mod",     // name of module exposed to Python
    "Python wrapper for custom C extension library.", // module documentation
    -1,
    symnmf_FunctionsTable
};

PyMODINIT_FUNC PyInit_symnmf_mod(void)
{
    PyObject *m;
    m = PyModule_Create(&symnmf_Module);
    if (!m) {
        return NULL;
    }
    return m;
}