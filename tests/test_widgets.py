from pyqml import QMLApplication, QMLComponent, QMLEngine
import sys

if __name__ == '__main__':
    app = QMLApplication(sys.argv)
    engine = QMLEngine()
    comp = QMLComponent(engine)
    comp.load_url("qrc:/gallery.qml")
    comp.create()
    app.run()
       