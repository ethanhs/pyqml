# -*- coding: utf-8 -*-
"""
This file is part of the pyqml project
gallery.py is a minimal example of running the
Qt Quick Controls 2 gallery demo.
"""
from pyqml import QMLApplication, QMLEngine
import sys



if __name__ == '__main__':
    app = QMLApplication(sys.argv)
    engine = QMLEngine()
    app.aboutQt()
    engine.set_resource("gallery.rcc")
    engine.load("gallery.qml")
    sys.exit(app.run())
