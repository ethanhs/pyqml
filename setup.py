#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import subprocess
import shutil
from typing import Dict
from setuptools import setup, Extension

# remove build dir, as it seems to be needed for extensions to build correctly.
build_dir = os.path.join(os.getcwd(), 'build')
if os.path.exists(build_dir):
    shutil.rmtree(build_dir)

class QMakeHelper:
    _qmake = {}  #type: Dict[str, str]
    def __init__(self, qmake_location: str = 'qmake'):
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
    def headers(self) -> str:
        base = self._qmake["QT_INSTALL_HEADERS"].strip()
        return base

    @property
    def libraries(self) -> str:
        return self._qmake['QT_INSTALL_LIBS'].strip()

    @property
    def version(self) -> str:
        return self._qmake['QT_VERSION'].strip()

q = QMakeHelper()
libs = ['Qt5Core', 'Qt5Gui', 'Qt5Widgets', 'Qt5Quick', 'Qt5Qml']
if '5.7' in q.version:
    libs.append('Qt5QuickControls2')
pyqml = Extension("pyqml", ["src/pyqml.cc"], include_dirs=[q.headers],
                  libraries=libs,
                  library_dirs=[q.libraries],
                  extra_compile_args=['/Zi'],
                  extra_link_args=['/DEBUG'])

setup(name='pyqml',
      version='0.1',
      description='CPython bindings to Qt\'s QML',
      classifiers=[
        'Development Status :: 2 - Pre-Alpha',
        'Intended Audience :: Developers',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6'
      ],
      ext_modules=[pyqml])
