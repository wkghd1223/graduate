import requests
import time

from PyQt5.QtWidgets import *
from datetime import date, timedelta
from bs4 import BeautifulSoup
from PyQt5.QtCore import *


class Crawler(QThread):

    change_value = pyqtSignal(int, int, str)

    _result = []
    query = None
    _page = 1

    def __init__(self, prevBtn, nextBtn):
        QThread.__init__(self)
        self.cond = QWaitCondition()
        self.mutex = QMutex()
        self.prevBtn = prevBtn
        self.nextBtn = nextBtn

    def set_query(self, query):
        self.query = query
        self._page = 1

    def set_page(self, page):
        self._page = page

    @property
    def page(self):
        return self._page

    @property
    def result(self):
        return self._result

    def run(self):
        self.newsCrawling(self.query, self._page)
        self.btnCheck()
        for i in range(len(self._result[0])):
            for j in range(len(self._result)):
                self.change_value.emit(i, j, self._result[j][i])

        # self.crawledResult.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)
        self.printCurPage()
        self.wait()

    def newsCrawling(self, query, page):

        self._result = []

        when = []
        headline = []
        source = []
        link = []

        s_date = str(date.today() - timedelta(days=7))
        e_date = str(date.today())
        s_from = s_date.replace("-", "")  # 우측부터 "-"을 찾아서 ""으로 바꿈
        e_to = e_date.replace("-", "")  # 우측부터 "-"을 찾아서 ""으로 바꿈

        url = "https://search.naver.com/search.naver?where=news&query=" + query \
              + "&sort=0&ds=" + s_date \
              + "&de=" + e_date \
              + "&nso=so%3Ar%2Cp%3Afrom" + s_from \
              + "to" + e_to \
              + "%2Ca%3A&start=" + str(page)

        req = requests.get(url)
        html = req.text
        soup = BeautifulSoup(html, 'html.parser')

        titles = soup.select('a._sp_each_title')
        companys = soup.select('span._sp_each_source')
        times = soup.select('dd.txt_inline')

        for title in titles:
            headline.append(title.text)
            link.append(title.get('href'))

        for company in companys:
            source.append(company.contents[0])

        for time in times:
            if len(time.contents) is 14:
                when.append(time.contents[7])
            else:
                when.append(time.contents[3])

        self._result.append(when)
        self._result.append(headline)
        self._result.append(source)
        self._result.append(link)

    def printCurPage(self):
        curPage = 1
        if self._page > 1:
            curPage = int((self._page + 9) / 10)

        print("현재 페이지:", curPage)

    def btnCheck(self):
        page = self._page
        length = len(self._result[0])

        if page > 1:
            self.prevBtn.setEnabled(True)
        elif page == 1:
            self.prevBtn.setEnabled(False)

        if length < 10:
            self.nextBtn.setEnabled(False)
        else:
            self.nextBtn.setEnabled(True)
