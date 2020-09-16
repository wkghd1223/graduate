import requests
from datetime import date, timedelta
from bs4 import BeautifulSoup
from PyQt5.QtCore import *

def newsCrawling(query, page):

    result = []
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

    result.append(when)
    result.append(headline)
    result.append(source)
    result.append(link)

    return result


class Crawler(QThread):
    result = []

    def __init__(self, table, prev, next):
        QThread.__init__(self)

    def run(self):
        print()

    def newsCrawling(self, query, page):

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

        self.result.append(when)
        self.result.append(headline)
        self.result.append(source)
        self.result.append(link)

        return result

