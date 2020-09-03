import sys
import csv
import pandas as pd
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import uic

STOCK_LIST_PATH = 'http://kind.krx.co.kr/corpgeneral/corpList.do?method=download&searchType=13'

class ChartWindow(QMainWindow):
    def __init__(self, parent):
        super(ChartWindow, self).__init__(parent)
        ui = "ui/chart.ui"
        uic.loadUi(ui, self)
        self.show()
        self.stocks = self.getStockList()

        self.searchBtn.clicked.connect(self.searchFunc)
        self.search.installEventFilter(self)
        self.stockList.clicked.connect(self.onClickItem)

    def getStockList(self):
        code_df = pd.read_html(STOCK_LIST_PATH, header=0)[0]  # 종목코드가 6자리이기 때문에 6자리를 맞춰주기 위해 설정해줌
        code_df.종목코드 = code_df.종목코드.map('{:06d}'.format)

        # 우리가 필요한 것은 회사명과 종목코드이기 때문에 필요없는 column들은 제외해준다.
        code_df = code_df[['회사명', '종목코드']] # 한글로된 컬럼명을 영어로 바꿔준다.
        code_df = code_df.rename(columns={'회사명': 'name', '종목코드': 'code'})
        return code_df

    # enter key를 이용하여 검색 가능
    def eventFilter(self, obj, event):
        if obj is self.search and event.type() == QEvent.KeyPress:
            if event.key() in (Qt.Key_Return, Qt.Key_Enter):
                self.searchFunc()
                return True
        return super().eventFilter(obj, event)

    # 검색 함수
    def searchFunc(self):
        word = self.search.toPlainText()
        searchedStock = []
        for idx, stock in self.stocks.iterrows():
            if word in stock['name']:
                searchedStock.append(stock['name'])
            if word in stock['code']:
                searchedStock.append(stock['name'])
        model = QStandardItemModel()
        for stock in searchedStock:
            model.appendRow(QStandardItem(stock))
        self.stockList.setModel(model)

    # 리스트 뷰 클릭 함수
    def onClickItem(self, idx):
        # get url
        code = self.stocks.query("name=='{}'".format(idx.data()))['code'].to_string(index=False).strip()
        url = 'http://finance.naver.com/item/sise_day.nhn?code={code}'.format(code=code)


        # 일 데이터
        df = pd.DataFrame()
        for page in range(1, 21):
            pg_url = '{url}&page={page}'.format(url=url, page=page)
            df = df.append(pd.read_html(pg_url, header=0)[0], ignore_index=True)

        df.dropna()
        print(df.head())

