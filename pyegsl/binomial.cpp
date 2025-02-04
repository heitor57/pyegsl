// #define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

static PyObject *
binomialpmf(PyObject *self, PyObject *args){
  int i,j;
  int k_num = 1;
  int p_num = 1;
  PyObject *k, *n, *p, *res = NULL;
  if (!PyArg_ParseTuple(args, "OOO", &k,&n,&p))
    return NULL;
  if(PyNumber_Check(n)){
    if(PyNumber_Check(k) && PyNumber_Check(p))
      res = PyFloat_FromDouble(gsl_ran_binomial_pdf(PyLong_AsLongLong(k),
						    PyFloat_AsDouble(p),
						    PyLong_AsLongLong(n)));
    else if(PySequence_Check(k) and PySequence_Check(p)){
      p_num = PySequence_Size(p);
      k_num = PySequence_Size(k);
      res = PyList_New(p_num);
      PyObject *sublist;
      for(i=0;i<p_num;i++){
	sublist = PyList_New(k_num);
	PyList_SetItem(res, i, sublist);
	for(j=0;j<k_num;j++){
	  PyList_SetItem(sublist,j,
			 PyFloat_FromDouble(gsl_ran_binomial_pdf(PyLong_AsLongLong(PySequence_GetItem(k, j)),
								 PyFloat_AsDouble(PySequence_GetItem(p, i)),
								 PyLong_AsLongLong(n))));
	}
      }
      
    }else if(PySequence_Check(k)){
      k_num = PySequence_Size(k);
      res = PyList_New(k_num);
      for(i=0;i<k_num;i++){
	PyList_SetItem(res,i,
		       PyFloat_FromDouble(gsl_ran_binomial_pdf(PyLong_AsLongLong(PySequence_GetItem(k,i)),
							       PyFloat_AsDouble(p),
							       PyLong_AsLongLong(n))));
      }
    }
    else if(PySequence_Check(p)){
      p_num = PySequence_Size(p);
      res = PyList_New(p_num);
      for(i=0;i<p_num;i++){
	PyList_SetItem(res,i,
		       PyFloat_FromDouble(gsl_ran_binomial_pdf(PyLong_AsLongLong(k),
							       PyFloat_AsDouble(PySequence_GetItem(p,i)),
							       PyLong_AsLongLong(n))));
      }
    }else{
      PyErr_SetString(PyExc_TypeError, "Not supported type passed");
    }
  }else{
    PyErr_SetString(PyExc_TypeError, "Not supported type passed");
  }

  return res;
}


static PyMethodDef binomialMethods[] = {
					{"binomialpmf", binomialpmf, METH_VARARGS, "(k=Tries,n=Total,p=Probability)\n\
k and p can be a list"},
					{NULL, NULL, 0, NULL}
};


static struct PyModuleDef binomialmodule = {
					    PyModuleDef_HEAD_INIT,
					    "binomial",
					    "Python interface to gsl binomial functions",
					    -1,
					    binomialMethods
};

PyMODINIT_FUNC PyInit_binomial(void) {
  return PyModule_Create(&binomialmodule);
}
