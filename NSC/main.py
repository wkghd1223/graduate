# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui/main.ui'
#
# Created by: PyQt5 UI code generator 5.15.0
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.
from chart import ChartWindow
import sys
from PyQt5.QtWidgets import *
from PyQt5 import uic

form_class = uic.loadUiType("ui/main.ui")[0]

class Main(QMainWindow, form_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.chartBtn.clicked.connect(self.chartBtnFunc)
        self.newsBtn.clicked.connect(self.newsBtnFunc)

    def chartBtnFunc(self):
        ChartWindow(self)
        print("chartBtn")

    def newsBtnFunc(self):
        print("chartBtn")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    myWindow = Main()

    myWindow.show()

    app.exec_()
