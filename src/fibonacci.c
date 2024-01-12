/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is free software: you can redistribute it and/or modify         *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  This file is distributed in the hope that it will be useful,              *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with this file.  If not, see <https://www.gnu.org/licenses/>.       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Simple example of using the C-Python API for extension modules.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 3, 2022                                                   *
 ******************************************************************************/

/*  All of the Python API tools and typedef's are found here.                 */
#include <Python.h>

/*  Fibonacci function prototypes are given here.                             */
#include "fibonacci.h"

/*  Helper macro for creating a Python wrapper to all of the C functions.     */
#define CREATE_PYTHON_FUNCTION(cname)                                          \
static PyObject * py##cname(PyObject *self, PyObject *args)                    \
{                                                                              \
    unsigned int n;                                                            \
                                                                               \
    if (!PyArg_ParseTuple(args, "I", &n))                                      \
        return NULL;                                                           \
                                                                               \
    return Py_BuildValue("I", cname(n));                                       \
}

/*  Create Python wrappers for all of the functions.                          */
CREATE_PYTHON_FUNCTION(fibonacci_iterative)
CREATE_PYTHON_FUNCTION(fibonacci_power_law)
CREATE_PYTHON_FUNCTION(fibonacci_power_law_naive)
CREATE_PYTHON_FUNCTION(fibonacci_recursive)
CREATE_PYTHON_FUNCTION(fibonacci_table)

/*  We're done with the helper macro now, so we can undefine it.              */
#undef CREATE_PYTHON_FUNCTION

/*  All functions available in the Python module.                             */
static PyMethodDef FibonacciMethods[] = {
    {
        "fibonacci_iterative",
        pyfibonacci_iterative,
        METH_VARARGS,
        "Computes the nth Fibonacci number using an iterative sum."
    },
    {
        "fibonacci_power_law",
        pyfibonacci_power_law,
        METH_VARARGS,
        "Computes the nth Fibonacci number using the power-law solution to"
        "the difference equation and some tools from libm."
    },
    {
        "fibonacci_power_law_naive",
        pyfibonacci_power_law_naive,
        METH_VARARGS,
        "Computes the nth Fibonacci number using the power-law solution to"
        "the difference equation. Powers are naively computed."
    },
    {
        "fibonacci_recursive",
        pyfibonacci_recursive,
        METH_VARARGS,
        "Computes the nth Fibonacci number using the recursive definition."
    },
    {
        "fibonacci_table",
        pyfibonacci_table,
        METH_VARARGS,
        "Computes the nth Fibonacci number using a precomputed table."
    },

    /*  End of array element. All entries have their zero values.             */
    {NULL, NULL, 0, NULL}
};

/*  The struct representing the Python module. You can import it at the       *
 *  python level via "import fibonacci".                                      */
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "fibonacci",
    NULL,
    -1,
    FibonacciMethods,
    NULL,
    NULL,
    NULL,
    NULL
};

/*  And lastly, the function that creates the Python module.                  */
PyMODINIT_FUNC
PyInit_fibonacci(void)
{
    return PyModule_Create(&moduledef);
}
