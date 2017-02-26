#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import subprocess
from setuptools import setup, Extension


class QMakeHelper:
    _qmake = {}
    def __init__(self, qmake_location='qmake'):
        raw_output = subprocess.Popen([qmake_location, '-query'], stdout=subprocess.PIPE)
        output = raw_output.stdout.read().decode()
        for line in output.split('\n'):
            try:
                index = line.index(':')
            except ValueError:
                continue
            index = line.find(':')
            if index < 0:
                continue
            key = line[:index]
            value = line[index + 1:]
            self._qmake[key] = value

    @property
    def headers(self):
        base = self._qmake["QT_INSTALL_HEADERS"].strip()
        return base

    @property
    def libraries(self):
        return self._qmake['QT_INSTALL_LIBS'].strip()

q = QMakeHelper()
pyqml = Extension("pyqml", ["src/pyqml.cc"], include_dirs=[q.headers],
                  libraries=['Qt5Core', 'Qt5Gui', 'Qt5Widgets', 'Qt5Quick', 'Qt5Qml'],
                  library_dirs=[q.libraries])

setup(name='pyqml',
      version='0.0.1',
      description='CPython bindings to Qt\'s QML',
      classifiers=[
        'Development Status :: 2 - Pre-Alpha',
        'Intended Audience :: Developers',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6'
      ],
      ext_modules=[pyqml])
