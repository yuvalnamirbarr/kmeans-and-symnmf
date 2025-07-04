# define PY_copy_pyobject_to_carraySIZE_T_CLEAN
# include <Python.h>
# include <stdlib.h>


int get_num_rows(PyObject* py_2darray) {
    return PyList_Size(py_2darray);
}

int get_num_cols(PyObject* py_2darray) {
    PyObject* first_row = PyList_GetItem(py_2darray, 0);
    return PyList_Size(first_row);
}


double** copy_pyobject_to_carray(PyObject* py_2darray, int rows, int cols) {

    double** c_array = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        c_array[i] = (double*)malloc(cols * sizeof(double));
        PyObject* row = PyList_GetItem(py_2darray, i);
        for (int j = 0; j < cols; j++) {
            PyObject* item = PyList_GetItem(row, j);
            c_array[i][j] = PyFloat_AsDouble(item);
        }
    }

    return c_array;
}

PyObject* carray_to_pylist(double** c_array, int rows, int cols) {
    
    PyObject* pylist = PyList_New(rows);
    for (int i = 0; i < rows; i++) {
        PyObject* row = PyList_New(cols);
        for (int j = 0; j < cols; j++) {
            PyList_SetItem(row, j, PyFloat_FromDouble(c_array[i][j]));
        }
        PyList_SetItem(pylist, i, row);
    }
    return pylist;
}

void free_carray(double** array, int rows) {

    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}