import sys
import csv
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import uic

STOCK_LIST_PATH = 'res/stock_list.csv'




class ChartWindow(QMainWindow):
    def __init__(self, parent):
        super(ChartWindow, self).__init__(parent)
        ui = "ui/chart.ui"
        uic.loadUi(ui, self)
        self.show()
        self.stocks = self.getStockList()
        self.searchBtn.clicked.connect(self.searchFunc)
        self.search.installEventFilter(self)

    def getStockList(self):
        f = open(STOCK_LIST_PATH, 'r')
        rdr = csv.reader(f)
        return list(rdr)
        # for line in rdr:
        #     line[0] # name
        #     line[1] # code
        #     line[2] # category
        #     line[3] # date of ipo

    def eventFilter(self, obj, event):
        if obj is self.search and event.type() == QEvent.KeyPress:
            if event.key() in (Qt.Key_Return, Qt.Key_Enter):
                self.searchFunc()
                return True
        return super().eventFilter(obj, event)

    def searchFunc(self):
        word = self.search.toPlainText()
        searchedStock = []
        for stock in self.stocks:
            if word in stock[0]:
                searchedStock.append(stock)
            if word in stock[1]:
                searchedStock.append(stock)
        model = QStandardItemModel()
        for stock in searchedStock:
            model.appendRow(QStandardItem(stock[0]))
        self.stockList.setModel(model)

        # print(self.stocks)