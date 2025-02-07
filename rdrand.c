#include <Python.h>
#include <stddef.h>
// #include <stdio.h>

static char const * const docstring = "";
#define FNCNAME rdrand
#define ARGS_SPECIFIERS 
#define PARAMETERS NULL

#define XSTR(_STR_) #_STR_
#define STR(_STR_) XSTR(_STR_)

int rdrand_step (uint64_t *rand)
{
		unsigned char ok;
		asm volatile ("rdrand %0; setc %1"
						: "=r" (*rand), "=qm" (ok));
		return (int) ok;
}



static PyObject *
rdrand(PyObject *self, PyObject *args) {
	uint64_t ull;
	int success = 0;


	if (!PyArg_ParseTuple(args, "", NULL))
	{
		return NULL;

	}


	for(int i=0; success==0 && i < 10; ++i)
	{
		success = rdrand_step(&ull);
	}

	return Py_BuildValue("K", ull);
}

static PyMethodDef rdrand_methods[] = {
	{"rdrand", rdrand, METH_VARARGS, docstring},
	{ NULL, NULL, 0, NULL }
};

static struct PyModuleDef rdrandmodule = {
	PyModuleDef_HEAD_INIT,
	"rdrand",
	NULL,
	-1,
	rdrand_methods
};



PyMODINIT_FUNC
PyInit_rdrand()
{
	return PyModule_Create(&rdrandmodule);
}

/*
#define XF(FN) PyInit_##FN
//PyInit_FNCNAME(void)

PyMODINIT_FUNC
XF(FNCNAME)(void)
{
	return PyModule_Create(&rdrandmodule);
}


*/
