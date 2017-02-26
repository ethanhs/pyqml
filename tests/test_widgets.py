from pyqml import QMLApplication, QMLComponent, QMLEngine
import sys

if __name__ == '__main__':
    app = QMLApplication(sys.argv)
    engine = QMLEngine()
    comp = QMLComponent(engine)
    comp.set_resource("gallery.rcc")
    comp.load_url("qrc:/gallery.qml")
    comp.create()
    sys.exit(app.run())
