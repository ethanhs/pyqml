#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
try:
    from skbuild import setup
except ImportError:
    print("Please install scikit-build ('pip install scikit-build' or 'pip3 install scikit-build' on some systems")
    sys.exit(1)

setup(name='pyqml',
      version='0.0.1',
      description='CPython bindings to Qt\'s QML',
      classifiers=[
        'Development Status :: 2 - Pre-Alpha',
        'Intended Audience :: Developers',
        'Natural Language :: English',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6'
      ])
