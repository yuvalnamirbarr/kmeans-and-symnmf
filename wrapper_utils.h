#ifndef WRAPPER_UTILS_H
#define WRAPPER_UTILS_H
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>

/*
    Extracts the number of rows from a Python 2D array object.
    Input: PyObject* (a Python 2D array)
    Output: Integer (number of rows)
*/
int get_num_rows(PyObject* py_2darray);
/*
    Extracts the number of columns from a Python 2D array object.
    Assumes all rows have the same number of columns.
    Input: PyObject* (a Python 2D array)
    Output: Integer (number of columns)
*/
int get_num_cols(PyObject* py_2darray);
/*
    Copies data from a Python 2D array to a dynamically allocated C 2D array.
    Input: 
        - PyObject* py_2darray: A Python 2D array
        - int rows: Number of rows in the Python array
        - int cols: Number of columns in the Python array
    Output: Pointer to a dynamically allocated C 2D array (double**)
*/
double** copy_pyobject_to_carray(PyObject* py_2darray, int rows, int cols);
/*
    Converts a C 2D array to a Python list of lists.
    Input:
        - double** c_array: Pointer to the C 2D array
        - int rows: Number of rows in the C array
        - int cols: Number of columns in the C array
    Output: PyObject* (a Python list of lists)
*/
PyObject* carray_to_pylist(double** c_array, int rows, int cols);
/*
    Frees memory allocated for a C 2D array.
    Input:
        - double** array: Pointer to the C 2D array
        - int rows: Number of rows in the array
    Output: None
*/
void free_carray(double** array, int rows);

#endif