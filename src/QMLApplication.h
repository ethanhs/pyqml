#pragma once
#ifndef QMLAPPLICATION_H
#define QMLAPPLICATION_H

#include <Python.h>
#include <QtCore/QtGlobal>
#include <QtWidgets/QApplication>
#include <QtCore/QSettings>
#if QT_VERSION > QT_VERSION_CHECK(5, 7, 0)
    #include <QtQuickControls2/QQuickStyle>
#endif


/* Create a QMLApplication type */
typedef struct {
    PyObject_HEAD
    PyObject* _qapp;
} qmlappObject;

//QMLApplication methods

static PyObject* qmlapp_init(qmlappObject *self, PyObject *args)
{
    if (QApplication::instance()) {
        PyErr_SetString(PyExc_RuntimeError, "A QApplication instance already exists.");
        return NULL;
    }
    PyObject* arg_vec;
    char** argv;
    int argc;
    if (!PyArg_ParseTuple(args, "O", &arg_vec)) {
		return NULL;
	}
	argc = PySequence_Length(arg_vec);
	argv = (char**) malloc(argc * sizeof(char*));
	for (int i = 0; i < argc; i++) {
	    argv[i] = PyUnicode_AsUTF8(PySequence_GetItem(arg_vec, i));
	}
    QApplication::setApplicationName("Gallery");
    QApplication::setOrganizationName("QtProject");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication* qapp_tmp = new QApplication(argc, argv);
    QSettings settings;
    // if we are using QtQuickControls2, take care of styles
    #if QT_VERSION > QT_VERSION_CHECK(5, 7, 0)
    QString style = QQuickStyle::name();
    if (!style.isEmpty()) {
        settings.setValue("style", style);
    } 
    else {
        QQuickStyle::setStyle(settings.value("style").toString());
    }
    #endif
    self->_qapp = PyCapsule_New(qapp_tmp, "qapp", NULL);
    return Py_None;
}

static void qmlapp_dealloc(qmlappObject* self) {
    QApplication* qapp = (QApplication *) PyCapsule_GetPointer(self->_qapp, "qapp");
    delete qapp;
}

static PyObject* qmlapp_aboutQt(qmlappObject* self) {
    QApplication* qapp = (QApplication *) PyCapsule_GetPointer(self->_qapp, "qapp");
    QMetaObject::invokeMethod(qapp, "aboutQt");
    return Py_None;
}

static PyObject* qmlapp_run(qmlappObject* self) {
    QApplication* qapp = (QApplication *) PyCapsule_GetPointer(self->_qapp, "qapp");
    int ret = qapp->exec();
    return Py_BuildValue("i", &ret);
}


static PyMethodDef qmlapp_methods[] = {
    {"aboutQt", (PyCFunction)qmlapp_aboutQt, METH_NOARGS, "Show an about Qt dialog"},
    {"run", (PyCFunction)qmlapp_run, METH_NOARGS, "Run the QML application"},
    {NULL}  /* Sentinel */
};

static PyTypeObject qmlappType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pyqml.QMLApplication",
    sizeof(qmlappObject),
    0,                         /* tp_itemsize */
    (destructor)qmlapp_dealloc,
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
    qmlapp_methods,
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)qmlapp_init,
    0,                         /* tp_alloc */
    0,                         /* tp_new */
};

#endif //QMLAPPLICATION_H