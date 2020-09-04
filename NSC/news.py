import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import uic
from NewsCrawler import crawling
from datetime import date, timedelta



class NewsWindow(QMainWindow):
    def __init__(self, parent):
        super(NewsWindow, self).__init__(parent)
        ui = "ui/news.ui"
        uic.loadUi(ui, self)

        self.show()
        self.setTable()
        self.searchBtn.clicked.connect(self.getNews)
        print(date.today())
    def getNews(self):
        today = datetime.date.today()

        maxpage = 2
        query = self.paramForSearch.text()
        s_date = datetime.date.today() - datetime.date.timedelta(days = -5000)
        e_date = datetime.date.today()
        c = crawling(maxpage, query, s_date, e_date)
        result = c.crawler(maxpage, query, s_date, e_date)
        print(s_date)

        for i in range(len(result)):
            for j in range(len(result[i])):
                self.crawledResult.setItem(i,j,QTableWidgetItem(result[i][j]))


    def setTable(self):

        self.crawledResult.setColumnCount(4)
        self.crawledResult.setRowCount(99)
        self.crawledResult.setHorizontalHeaderLabels(["날짜", "제목", "회사", "URL"])




