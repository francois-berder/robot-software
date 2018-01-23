import numpy as np
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtGui
import queue
import threading
import time

class QtPlotter:
    def __init__(self, buffer_size):
        self.ports = []
        self.timer = pg.QtCore.QTimer()
        self.win = pg.GraphicsWindow()
        self.ax = self.win.addPlot()
        self.timer.timeout.connect(self.update)
        self.timer.start(0)
        self.ax.setAspectLocked(True)
        self.buffer_size = buffer_size

    def getPort(self):
        q = queue.Queue()
        plt = self.ax
        self.ports.append((q, plt))
        return q

    def update(self):
        for q, plt in self.ports:
            try:
                data = q.get(block=False)
                plt.clear()
                for index, variable in enumerate(data):
                    plt.plot(
                        np.asarray(data[variable]['time'][-self.buffer_size:]).flatten(),
                        np.asarray(data[variable]['value'][-self.buffer_size:]).flatten(),
                        pen=(index, len(data)), symbol="o",
                        symbolPen=pg.mkPen({'color': "#00FFFF", 'width': 2}),
                        symbolSize=1
                    )
            except queue.Empty:
                pass

def qt_loop():
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()

class Model:
    def __init__(self):
        self.data = {
            'x': {
                'time': np.array([0]),
                'value': np.array([0]),
            },
            'y': {
                'time': np.array([0]),
                'value': np.array([0]),
            },
        }
        threading.Thread(target=self.run).start()

    def get_data(self):
        return self.data

    def run(self):
        while True:
            self.data['x']['time'] = np.append(self.data['x']['time'], self.data['x']['time'][-1] + 0.1)
            self.data['y']['time'] = np.append(self.data['y']['time'], self.data['y']['time'][-1] + 0.1)
            self.data['x']['value'] = np.append(self.data['x']['value'], np.random.random(size=(1,1)))
            self.data['y']['value'] = np.append(self.data['y']['value'], np.random.random(size=(1,1)))
            time.sleep(0.1)

class Controller:
    def __init__(self):
        self.viewer = QtPlotter(buffer_size=100)
        self.curve = self.viewer.getPort()
        self.model = Model()
        threading.Thread(target=self.run).start()

    def run(self):
        while True:
            self.curve.put(self.model.get_data())
            time.sleep(1)

def main():
    plot_controller = Controller()
    qt_loop()

if __name__ == "__main__":
    main()
