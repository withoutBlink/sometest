from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout
import json

qtapp = QApplication([])
qtwindow = QWidget()
qtlayout = QVBoxLayout()
start_but = QPushButton('Start')
stop_but = QPushButton('Stop')
qtlayout.addWidget(start_but)
qtlayout.addWidget(stop_but)
qtwindow.setLayout(qtlayout)
qtwindow.show()
qtapp.exec()



