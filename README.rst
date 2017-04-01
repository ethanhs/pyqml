=====
PyQML
=====

PyQml is a Python C extension binding a minimal subset of Qt's QML api for the rapid development of QML based UIs with
Python. It is written to be portable, and is tested on Windows (Linux support planned for 0.1 release). Contributions
for MacOS support are welcome!

Currently, PyQml supports Python 3.5 and 3.6, but one may be able to get it work on 3.4 on Linux. See building for how to build.

Status
======

As of right now, PyQml can run programs such as the Qt Quick Controls 2 Gallery. It is still very early stages of the library, and much work is left to be done.

Building
========

As of right now, one must first install Qt>=5.7, either through your operating systems package manager, or through the official installers provided by the Qt Company.
You also need to add the path to the qmake executable to your PATH. Then one should be able to run `python setup.py install` or if you would like to build the binary `python setup.py build_ext`


NOTE
====

This software is considered pre-alpha. It may eat your computer for lunch if it feels like it. I make no garuntees that it will work for you or is safe to use. Use at your own risk!


License
=======
Copyright 2017 Ethan Smith

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
