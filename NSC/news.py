import sys
import time

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import uic
from datetime import date, timedelta
import webbrowser
from newCrawler import Crawler
from settings import resource_path

form = resource_path("ui/news.ui")

class NewsWindow(QMainWindow):
    def __init__(self, parent):
        super(NewsWindow, self).__init__(parent)

        uic.loadUi(form, self)

        self.show()
        self.crawler = Crawler( prevBtn=self.prevBtn, nextBtn=self.nextBtn)

        self.setTable()

        self.nextBtn.setEnabled(False)
        self.prevBtn.setEnabled(False)

        self.searchBtn.clicked.connect(self.searchFunc)
        self.nextBtn.clicked.connect(self.clickNextBtn)
        self.prevBtn.clicked.connect(self.clickPrevBtn)

        self.crawledResult.itemClicked.connect(self.openLink)
        self.crawler.change_value.connect(self.some_function)

        self.paramForSearch.installEventFilter(self)

    def searchFunc(self):
        query = self.paramForSearch.text()
        self.crawler.set_query(query)
        self.startCrawler()

    # enter key를 이용하여 검색 가능
    def eventFilter(self, obj, event):
        if obj is self.paramForSearch and event.type() == QEvent.KeyPress:
            if event.key() in (Qt.Key_Return, Qt.Key_Enter):
                self.searchFunc()
                return True
        return super().eventFilter(obj, event)

    def setTable(self):
        self.crawledResult.setRowCount(10)
        self.crawledResult.setColumnCount(3)
        self.crawledResult.setHorizontalHeaderLabels(["시간", "제목", "출처"])

    def clickNextBtn(self):
        page = self.crawler.page
        self.crawler.set_page(page+10)
        self.startCrawler()

    def clickPrevBtn(self):
        page = self.crawler.page
        self.crawler.set_page(page - 10)
        self.startCrawler()

    def openLink(self, item):
        result = self.crawler.result
        if item.column() == 1:
            webbrowser.open(result[3][item.row()])

    @pyqtSlot(int, int, str)
    def some_function(self, r, c, text):
        it = self.crawledResult.item(r, c)
        if it:
            it.setText(text)
        else:
            it = QTableWidgetItem(text)
            self.crawledResult.setItem(r, c, it)

    def startCrawler(self):
        if self.crawler.isRunning():
            self.crawler.terminate()
            self.crawler.wait()
        self.crawler.start()
