#pragma once
#ifndef QMLENGINE_H
#define QMLENGINE_H

#include <Python.h>
#include <QtWidgets/QApplication>
#include <QtQml/QQmlEngine>

/* Create a QMLEngine type */
typedef struct {
    PyObject_HEAD
    PyObject* _qengine;
} qmlengineObject;

/* QMLEngine methods */

static PyObject* qmlengine_init(qmlengineObject *self, PyObject *args)
{
    QQmlEngine* engine = new QQmlEngine();
    QObject::connect(engine, SIGNAL(quit()), QApplication::instance(), SLOT(quit()));
    self->_qengine = PyCapsule_New(engine, "qengine", NULL);
    return Py_None;
}

static void qmlengine_dealloc(qmlengineObject* self) {
    QQmlEngine* qengine = (QQmlEngine *) PyCapsule_GetPointer(self->_qengine, "qengine");
    delete qengine;
}

static PyObject* qmlengine_add_import(qmlengineObject* self, PyObject* args) {
    char* path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
		return NULL;
	}
    QQmlEngine* qengine = (QQmlEngine *) PyCapsule_GetPointer(self->_qengine, "qengine");
    qengine->addImportPath(path);
    return Py_None;
}

static PyMethodDef qmlengine_methods[] = {
    {"add_import", (PyCFunction)qmlengine_add_import, METH_VARARGS, "Add a path to search for QML import files"},
    {NULL}  /* Sentinel */
};

static PyTypeObject qmlengineType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pyqml.QMLEngine",
    sizeof(qmlengineObject),
    0,                         /* tp_itemsize */
    (destructor)qmlengine_dealloc,
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "Manages QML applications",
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    qmlengine_methods,
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)qmlengine_init,
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};
#endif //QMLENGINE_H