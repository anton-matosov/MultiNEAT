


#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iostream>

#if defined(PY_UFUNC_UNIQUE_SYMBOL)
#define PyUFunc_API PY_UFUNC_UNIQUE_SYMBOL
#endif

#if defined(NO_IMPORT) || defined(NO_IMPORT_UFUNC)
extern void **PyUFunc_API;
#else
#if defined(PY_UFUNC_UNIQUE_SYMBOL)
void **PyUFunc_API;
#else
static void **PyUFunc_API=NULL;
#endif
#endif

static int
_import_umath(void)
{
  PyObject *numpy = PyImport_ImportModule("numpy.core.umath");
  PyObject *c_api = NULL;

  if (numpy == NULL) {
      PyErr_SetString(PyExc_ImportError, "numpy.core.umath failed to import");
      return -1;
  }
  c_api = PyObject_GetAttrString(numpy, "_UFUNC_API");
  Py_DECREF(numpy);
  if (c_api == NULL) {
      PyErr_SetString(PyExc_AttributeError, "_UFUNC_API not found");
      return -1;
  }

#if PY_VERSION_HEX >= 0x03000000
  if (!PyCapsule_CheckExact(c_api)) {
      PyErr_SetString(PyExc_RuntimeError, "_UFUNC_API is not PyCapsule object");
      Py_DECREF(c_api);
      return -1;
  }
  PyUFunc_API = (void **)PyCapsule_GetPointer(c_api, NULL);
#else
  if (!PyCObject_Check(c_api)) {
      PyErr_SetString(PyExc_RuntimeError, "_UFUNC_API is not PyCObject object");
      Py_DECREF(c_api);
      return -1;
  }
  PyUFunc_API = (void **)PyCObject_AsVoidPtr(c_api);
#endif
  Py_DECREF(c_api);
  if (PyUFunc_API == NULL) {
      PyErr_SetString(PyExc_RuntimeError, "_UFUNC_API is NULL pointer");
      return -1;
  }
  return 0;
}

void wrap_fill2(boost::python::numpy::ndarray const & array)
{

}

BOOST_PYTHON_MODULE(_MultiNEAT)
{
    Py_Initialize();

    // if (_import_umath() < 0) {
    //     PyErr_Print();
    //     PyErr_SetString(PyExc_ImportError,
    //             "DUMB numpy.core.umath failed to import");
    // }

    boost::python::numpy::initialize();
    PyErr_Print();
    
    boost::python::def("fill", wrap_fill2);

//    std::wcout << L"[DBG] Py_GetPythonHome: " << Py_GetPythonHome() << std::endl;
//     std::wcout << L"[DBG] Py_GetProgramFullPath: " << Py_GetProgramFullPath() << std::endl;
//     std::wcout << L"[DBG] Py_GetPrefix: " << Py_GetPrefix() << std::endl;
//     std::wcout << L"[DBG] Py_GetExecPrefix: " << Py_GetExecPrefix() << std::endl;
//     std::wcout << L"[DBG] Py_GetPath: " << Py_GetPath() << std::endl;
// //
// //    std::cout << "[DBG] Py_GetVersion: " << Py_GetVersion() << std::endl;
// //    std::cout << "[DBG] Py_GetPlatform: " << Py_GetPlatform() << std::endl;
// //    std::cout << "[DBG] Py_GetCopyright: " << Py_GetCopyright() << std::endl;
// //    std::cout << "[DBG] Py_GetCompiler: " << Py_GetCompiler() << std::endl;
// //    std::cout << "[DBG] Py_GetBuildInfo: " << Py_GetBuildInfo() << std::endl;

//     PyRun_SimpleString("import numpy as np\nprint(np.random.randn(5))");


}