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

    def getNews(self):
        query = self.paramForSearch.text()
        start = time.time()
        global result
        global page
        result = newsCrawling(query, page)

        print("크롤링 기사 개수 :", len(result[0]))
        print("소요 시간: ", round(time.time() - start, 6))

    def setTable(self):
        self.crawledResult.setColumnCount(4)
        self.crawledResult.setHorizontalHeaderLabels(["날짜", "제목", "출처", "URL"])

    def openLink(self, item):
        if item.column() == 1:
            webbrowser.open(self.crawledResult.item(item.row(), 3).text())

    def setNews(self):
        global result

        self.setPrevBtn()

        self.crawledResult.setRowCount(10)

        for i in range(len(result[0])):
            for j in range(len(result)):
                self.crawledResult.setItem(i, j, QTableWidgetItem(result[j][i]))

        if page > 1:
            self.crawledResult.itemClicked.disconnect(self.openLink)

        self.crawledResult.itemClicked.connect(self.openLink)
        self.crawledResult.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)

        result = []
        self.nextBtn.setEnabled(True)
        print("현재 페이지 :", page)
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

