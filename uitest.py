from websocket import WebSocket
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPalette
from PyQt5.QtWidgets import (QApplication, QPushButton, QVBoxLayout, QWidget)
# import routine

class TestItem(QApplication, QWidget): 
    def __init__(self): 
        self.qtapp = QApplication([])
        self.qtwindow = QWidget()
        self.start_butt = QPushButton('Start')
        self.start_butt.clicked.connect(self.newconn)
        self.stop_butt = QPushButton('Stop')
        self.stop_butt.clicked.connect(self.closeconn)
        self.qtlayout = QVBoxLayout()
        self.qtlayout.addWidget(self.start_butt)
        self.qtlayout.addWidget(self.stop_butt)
        self.qtwindow.setLayout(self.qtlayout)
        # self.wbsc = WebSocket()
        # self.wbsc.connect(self.server_addr)

    def runApp(self) -> int:
        return self.qtapp.exec_()

    def newconn(self): 
        server_addr = "ws://127.0.0.1:7063/tmix/items"
        self.wbsc = WebSocket()
        self.wbsc.connect(server_addr)

    def newlogout(self) -> None:
        print("Button Pushed")

    def closeconn(self): 
        self.wbsc.close()    

    def showWindow(self) -> int:
        return self.qtwindow.show()

if __name__ == "__main__":
    item = TestItem()
    item.showWindow()
    item.runApp()

