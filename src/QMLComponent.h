#pragma once
#ifndef QMLCOMPONENT_H
#define QMLCOMPONENT_H
#include <Python.h>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlEngine>
#include <QtCore/QUrl>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QResource>
#include "QMLEngine.h"


/* Create a QMLComponent type */
typedef struct {
    PyObject_HEAD
    PyObject* _qcomp;
} qmlcomponentObject;

/* QMLComponent methods */

static PyObject* qmlcomponent_init(qmlcomponentObject *self, PyObject *args)
{
    qmlengineObject* engine;
    if (!PyArg_ParseTuple(args, "O", &engine)) {
		return Py_None;
	}
	QQmlEngine* qengine = (QQmlEngine *) PyCapsule_GetPointer((PyObject*) engine->_qengine, "qengine");
    QQmlComponent* component = new QQmlComponent(qengine);
    self->_qcomp = PyCapsule_New(component, "qcomp", NULL);
    return Py_None;
}

static void qmlcomponent_dealloc(qmlcomponentObject* self) {
    QQmlComponent* component = (QQmlComponent*) PyCapsule_GetPointer(self->_qcomp, "qcomp");
    delete component;
}

static PyObject* qmlcomponent_setresource(qmlcomponentObject* self, PyObject* args) {
    char* path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
		return NULL;
	}
	QResource::registerResource(QString(path));
    return Py_None;
}

static PyObject* qmlcomponent_load_path(qmlcomponentObject* self, PyObject* args) {
    char* path;
    if (!PyArg_ParseTuple(args, "s", &path)) {
		return NULL;
	}
	QFile* file = new QFile(QString(path));
	if (!file->exists()) {
	    char* err = (char*) malloc((22 + strlen(path)) * sizeof(char));
	    strcpy(err, "File does not exist: ");
	    strcpy(err, path);
	    PyErr_SetString(PyExc_RuntimeError, err);
	}
    QQmlComponent* component = (QQmlComponent*) PyCapsule_GetPointer(self->_qcomp, "qcomp");
    component->loadUrl(QUrl::fromLocalFile(file->fileName()));
    return Py_None;
}

static PyObject* qmlcomponent_load_url(qmlcomponentObject* self, PyObject* args) {
    char* url;
    if (!PyArg_ParseTuple(args, "s", &url)) {
		return NULL;
	}
    QQmlComponent* component = (QQmlComponent*) PyCapsule_GetPointer(self->_qcomp, "qcomp");
    component->loadUrl(QUrl(QString(url)));
    if(!component->errorString().isEmpty()) {
        PyErr_SetString(PyExc_RuntimeError, component->errorString().toUtf8().constData());
    }
    return Py_None;
}

static PyObject* qmlcomponent_create(qmlcomponentObject* self) {
    QQmlComponent* component = (QQmlComponent*) PyCapsule_GetPointer(self->_qcomp, "qcomp");
    PyErr_SetString(PyExc_RuntimeError, component->errorString().toUtf8().constData());
    QObject* obj = component->create();
    if (!obj) {
        return NULL;
    }
    QQmlEngine::setObjectOwnership(obj, QQmlEngine::JavaScriptOwnership);
    return Py_None;
}

static PyMethodDef qmlcomponent_methods[] = {
    {"create", (PyCFunction)qmlcomponent_create, METH_NOARGS, "Create a new instance of the component"},
    {"set_resource", (PyCFunction) qmlcomponent_setresource, METH_VARARGS, "Set the .rcc Qt resource file"},
    {"load_path", (PyCFunction)qmlcomponent_load_path, METH_VARARGS, "Load a QML file from a path."},
    {"load_url", (PyCFunction)qmlcomponent_load_url, METH_VARARGS, "Load a QML file from a qrc URL."},
    {NULL}  /* Sentinel */
};

static PyTypeObject qmlcomponentType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pyqml.QMLComponent",
    sizeof(qmlcomponentObject),
    0,                         /* tp_itemsize */
    (destructor)qmlcomponent_dealloc,
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
    "Hosts QML programs",
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    qmlcomponent_methods,
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)qmlcomponent_init,
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};

#endif QMLCOMPONENT_H