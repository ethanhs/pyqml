#include <Python.h>

#if PY_MAJOR_VERSION != 3
#error "This library only supports Python 3"
#endif

#include "QMLComponent.h"
#include "QMLEngine.h"
#include "QMLApplication.h"
#include <QtCore/QtGlobal>

#ifdef __cplusplus
extern "C" {
#endif

static PyObject* pyqml_version(PyObject* self) {
    return Py_BuildValue("s", "0.0.1");
}

static PyObject* pyqml_qt_version(PyObject* self) {
    return Py_BuildValue("s", qVersion());
}

static PyMethodDef PyQMLMethods[] =
{
    {"version", (PyCFunction)pyqml_version, METH_NOARGS, "The PyQML version."},
    {"qt_version", (PyCFunction)pyqml_qt_version, METH_NOARGS, "The Qt version PyQML was compiled against."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pyqmlmodule = {
   PyModuleDef_HEAD_INIT,
   "pyqml",
   NULL, /* TODO: add docs */
   -1,
   PyQMLMethods
};

PyMODINIT_FUNC
PyInit_pyqml(void)
{
    PyObject* m;

    /* QMLApplication */
    qmlappType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&qmlappType) < 0)
        return NULL;

    /* QMLEngine */
    qmlengineType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&qmlengineType) < 0)
        return NULL;

    /* QMLComponent
    qmlcomponentType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&qmlcomponentType) < 0)
        return NULL;


    */

    m = PyModule_Create(&pyqmlmodule);
    if (m == NULL)
        return NULL;
    Py_INCREF(&qmlappType);
    Py_INCREF(&qmlengineType);
    //Py_INCREF(&qmlcomponentType);
    PyModule_AddObject(m, "QMLApplication", (PyObject*) &qmlappType);
    PyModule_AddObject(m, "QMLEngine", (PyObject*) &qmlengineType);
    //PyModule_AddObject(m, "QMLComponent", (PyObject*) &qmlcomponentType);
    return m;
}

#ifdef __cplusplus
}
#endif