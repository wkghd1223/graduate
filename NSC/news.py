import sys
import time

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import uic
from NewsCrawler import crawling
from datetime import date, timedelta
import webbrowser

global realPage
global result
global pagingCount
global pagingHistory
result = []
realPage = 1
pagingCount = 1
pagingHistory = []


class NewsWindow(QMainWindow):
    def __init__(self, parent):
        super(NewsWindow, self).__init__(parent)

        ui = "ui/news.ui"
        uic.loadUi(ui, self)

        self.show()
        self.setTable()
        self.setPrevBtn()

        self.searchBtn.clicked.connect(self.initPageNum)
        self.searchBtn.clicked.connect(self.getNews)
        self.searchBtn.clicked.connect(self.setNews)

        self.nextBtn.clicked.connect(self.clickNextBtn)
        self.nextBtn.clicked.connect(self.setNews)

        self.prevBtn.clicked.connect(self.clickPrevBtn)
        self.prevBtn.clicked.connect(self.setNews)

    def getNews(self):
        global realPage
        global result

        self.initPageNum()

        query = self.paramForSearch.text()
        s_date = str(date.today()-timedelta(days=7))
        e_date = str(date.today())
        start = time.time()
        c = crawling(realPage, query, s_date, e_date, result)
        result = c.crawler(realPage, query, s_date, e_date, result)

        print("크롤링 기사 개수 :", len(result))
        print("소요 시간: ", round(time.time() - start, 6))

    def setTable(self):
        self.crawledResult.setColumnCount(4)
        self.crawledResult.setHorizontalHeaderLabels(["날짜", "제목", "출처", "URL"])
        self.setNextBtn()

    def openLink(self, item):
        if item.column() == 1:
            webbrowser.open(self.crawledResult.item(item.row(), 3).text())

    def setNews(self):
        global result

        self.setPrevBtn()
        self.setNextBtn()

        self.crawledResult.setRowCount(len(result))

        for i in range(len(result)):
            for j in range(len(result[i])):
                self.crawledResult.setItem(i, j, QTableWidgetItem(result[i][j]))

        self.crawledResult.itemClicked.connect(self.openLink)
        self.crawledResult.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)
        print("현재페이지:", realPage)
        result = []

    def initPageNum(self):
        global realPage
        realPage = 1

    def clickNextBtn(self):
        global realPage
        global result
        global pagingCount
        global pagingHistory

        realPage = realPage + 1
        pagingCount = 1

        query = self.paramForSearch.text()
        s_date = str(date.today() - timedelta(days=7))
        e_date = str(date.today())
        start = time.time()

        c = crawling(realPage, query, s_date, e_date, result)
        result = c.crawler(realPage, query, s_date, e_date, result)

        print("페이징카운트:", pagingCount)

        if len(result) < 10:
            while len(result) < 10:
                realPage = realPage + 1

                c = crawling(realPage, query, s_date, e_date, result)
                result = c.crawler(realPage, query, s_date, e_date, result)
                pagingCount += 1
                print("페이징카운트:", pagingCount)

        pagingHistory.append(pagingCount)

        print("크롤링 기사 개수 :", len(result))
        print("소요 시간: ", round(time.time() - start, 6))
        print("pagingHistory:", pagingHistory)

    def setPrevBtn(self):
        global realPage
        if realPage > 1:
            self.prevBtn.setEnabled(True)
        elif realPage is 1:
            self.prevBtn.setEnabled(False)

    def setNextBtn(self):
        global result
        self.nextBtn.setEnabled(False)
        if len(result) > 0:
            self.nextBtn.setEnabled(True)

    def clickPrevBtn(self):
        global realPage
        global result
        global pagingCount
        global pagingHistory

        pagingCount = 1

        if len(pagingHistory) <= 1:
            pagingHistory = []
            realPage = 1

        elif realPage > 1:
            if len(pagingHistory) >= 2:
                realPage = realPage - (pagingHistory[-1]+pagingHistory[-2]) + 1
                del pagingHistory[-1]

        query = self.paramForSearch.text()
        s_date = str(date.today() - timedelta(days=7))
        e_date = str(date.today())
        start = time.time()

        c = crawling(realPage, query, s_date, e_date, result)
        result = c.crawler(realPage, query, s_date, e_date, result)

        print("페이징카운트:", pagingCount)

        if len(result) < 10:
            while len(result) < 10:
                realPage = realPage + 1

                c = crawling(realPage, query, s_date, e_date, result)
                result = c.crawler(realPage, query, s_date, e_date, result)
                pagingCount += 1
                print("페이징카운트:", pagingCount)

        print("크롤링 기사 개수 :", len(result))
        print("소요 시간: ", round(time.time() - start, 6))
        print("pagingHistory:", pagingHistory)
