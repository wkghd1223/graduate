import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import uic
from NewsCrawler import crawling
from datetime import date, timedelta
import webbrowser

class NewsWindow(QMainWindow):
    def __init__(self, parent):
        super(NewsWindow, self).__init__(parent)

        ui = "ui/news.ui"
        uic.loadUi(ui, self)

        self.show()
        self.setTable()
        self.searchBtn.clicked.connect(self.getNews)

    def getNews(self):
        maxpage = 2
        query = self.paramForSearch.text()
        s_date = str(date.today()-timedelta(days=5))
        e_date = str(date.today())

        c = crawling(maxpage, query, s_date, e_date)
        result = c.crawler(maxpage, query, s_date, e_date)

        print(len(result))

        self.crawledResult.setRowCount(len(result))

        for i in range(len(result)):
            for j in range(len(result[i])):
                self.crawledResult.setItem(i,j,QTableWidgetItem(result[i][j]))

        self.crawledResult.itemClicked.connect(self.OpenLink)
        self.crawledResult.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)

    def setTable(self):
        self.crawledResult.setColumnCount(4)
        self.crawledResult.setRowCount(50)
        self.crawledResult.setHorizontalHeaderLabels(["날짜", "제목", "출처", "URL"])

    def OpenLink(self, item):
        if item.column() == 1:
            webbrowser.open(self.crawledResult.item(item.row(),3).text())