import sys
import time

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import uic
from newCrawler import newsCrawling
from datetime import date, timedelta
import webbrowser

global result
global page
page = 1


class NewsWindow(QMainWindow):
    def __init__(self, parent):
        super(NewsWindow, self).__init__(parent)

        ui = "ui/news.ui"
        uic.loadUi(ui, self)

        self.show()
        self.setTable()
        self.setPrevBtn()
        self.nextBtn.setEnabled(False)

        self.searchBtn.clicked.connect(self.getNews)
        self.searchBtn.clicked.connect(self.setNews)

        self.nextBtn.clicked.connect(self.clickNextBtn)
        self.nextBtn.clicked.connect(self.setNews)

        self.prevBtn.clicked.connect(self.clickPrevBtn)
        self.prevBtn.clicked.connect(self.setNews)

        self.crawledResult.itemClicked.connect(self.openLink)

    def getNews(self):
        query = self.paramForSearch.text()
        start = time.time()
        global result
        global page
        result = newsCrawling(query, page)

        print("크롤링 기사 개수 :", len(result[0]))
        print("소요 시간: ", round(time.time() - start, 6))

    def setTable(self):
        self.crawledResult.setColumnCount(3)
        self.crawledResult.setHorizontalHeaderLabels(["시간", "제목", "출처"])

    def openLink(self, item):
        global result

        if item.column() == 1:
            webbrowser.open(result[3][item.row()])

    def setNews(self):
        global result

        self.setPrevBtn()

        self.crawledResult.setRowCount(10)

        for i in range(len(result[0])):
            for j in range(len(result)):
                self.crawledResult.setItem(i, j, QTableWidgetItem(result[j][i]))

        self.crawledResult.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)

        self.nextBtn.setEnabled(True)
        self.printCurPage()
        print("")

    def clickNextBtn(self):
        global result
        global page
        query = self.paramForSearch.text()
        start = time.time()
        page += 10
        result = newsCrawling(query, page)

        print("크롤링 기사 개수 :", len(result[0]))
        print("소요 시간: ", round(time.time() - start, 6))

    def setPrevBtn(self):
        global page
        if page > 1:
            self.prevBtn.setEnabled(True)
        elif page is 1:
            self.prevBtn.setEnabled(False)

    def clickPrevBtn(self):
        global page
        global result

        query = self.paramForSearch.text()
        start = time.time()
        page -= 10

        result = newsCrawling(query, page)

        print("크롤링 기사 개수 :", len(result[0]))
        print("소요 시간: ", round(time.time() - start, 6))

    def printCurPage(self):
        global page
        curPage = 1
        if page > 1:
            curPage = int((page + 9) / 10)

        print("현재 페이지:", curPage)
