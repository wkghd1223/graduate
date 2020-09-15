import sys
import numpy as np
import os
from datetime import datetime as dt
import datetime
import pandas as pd
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import uic
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import matplotlib.ticker as ticker
from matplotlib.widgets import Slider
from mplfinance.original_flavor import candlestick2_ohlc
from matplotlib.dates import DateFormatter, WeekdayLocator, DayLocator, MONDAY
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas

from policy_learner import PolicyLearner
from policy_network import PolicyNetwork
import settings
import data_manager
import time

DAY = '일'
WEEK = '주'
MONTH = '월'
STOCK_LIST_PATH = 'http://kind.krx.co.kr/corpgeneral/corpList.do?method=download&searchType=13'

class ChartWindow(QMainWindow):
    def __init__(self, parent):
        super(ChartWindow, self).__init__(parent)
        ui = "ui/chart.ui"
        uic.loadUi(ui, self)
        self.show()

        self.code = None
        self.df = pd.DataFrame()
        self.stocks = self.getStockList()
        self.term = DAY
        self.isClicked = False

        self.fig = plt.Figure()
        self.canvas = FigureCanvas(self.fig)

        self.initUi()

    def initUi(self):
        self.dayWeekMonth.addItem(DAY)
        self.dayWeekMonth.addItem(WEEK)
        self.dayWeekMonth.addItem(MONTH)

        self.searchBtn.clicked.connect(self.searchFunc)
        self.learnBtn.clicked.connect(self.learnFunc)
        self.search.installEventFilter(self)
        self.stockList.clicked.connect(self.onClickList)
        # 콤보박스 리스너
        self.dayWeekMonth.activated[str].connect(self.onDayWeekMonthChanged)
        self.onDayWeekMonthChanged(self.dayWeekMonth.currentText())

        # 위젯
        self.layout.addWidget(self.canvas)

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
            if word in stock['code'] and not (stock['name'] in searchedStock):
                searchedStock.append(stock['name'])
        model = QStandardItemModel()
        for stock in searchedStock:
            model.appendRow(QStandardItem(stock))
        self.stockList.setModel(model)

    # 리스트 클릭 리스너
    def onClickList(self, idx):
        # 한번이라도 리스트 뷰를 클릭해야 콤보박스 변경 시 그래프가 바뀐다
        self.isClicked = True
        self.getStockData(idx)
        self.showGraph()

    # 콤보박스 변경 리스너
    def onDayWeekMonthChanged(self, t):
        self.term = t
        if self.isClicked:
            self.showGraph()

    # 주가데이터 가져오는 함수
    def getStockData(self, idx):
        # get url
        self.code = self.stocks.query("name=='{}'".format(idx.data()))['code'].to_string(index=False).strip()
        code = self.code
        url = 'http://finance.naver.com/item/sise_day.nhn?code={code}'.format(code=code)

        # 일 데이터
        df = pd.DataFrame()

        for page in range(1, 21):
            pg_url = '{url}&page={page}'.format(url=url, page=page)
            df = df.append(pd.read_html(pg_url, header=0)[0], ignore_index=True)

        df.drop(['전일비'], axis='columns', inplace=True)
        df.rename(columns={'날짜': 'date', '종가': 'close', '시가': 'open', '고가': 'high', '저가': 'low', '거래량': 'volume'},
                  inplace=True)

        df.sort_values(by=['date'], axis=0, ascending=True, inplace=True)
        df.dropna(inplace=True)
        self.df = df

    # 리스트 뷰 클릭 함수
    def showGraph(self):

        df = self.df
        ndf = df.copy()

        term = 1
        if self.term == DAY:
            term = 1
        if self.term == WEEK:
            term = 7
        if self.term == MONTH:
            term = 30
        curr = 0
        idx = 0
        for i, row in df.iterrows():
            if idx == 0:
                curr = i
                # curr = dt.strptime(row['date'], "%Y.%m.%d")
            else:
                timeGap = (dt.strptime(df.loc[curr]['date'], "%Y.%m.%d") - dt.strptime(row['date'], "%Y.%m.%d")).days
                if abs(timeGap) < term:
                    if row['high'] > df.loc[curr]['high']:
                        ndf.loc[curr, 'high'] = row['high']
                    if row['low'] > df.loc[curr]['low']:
                        ndf.loc[curr, 'low'] = row['low']
                    ndf.loc[curr, 'close'] = row['close']
                    ndf.drop(index=i, inplace=True)
                else:
                    curr = i
            idx += 1

        self.fig.clear()
        ax = self.fig.add_subplot(111)

        # mondays = WeekdayLocator(MONDAY)
        # alldays = DayLocator()
        # weekFormatter = DateFormatter("%b %d")
        # dayFormatter = DateFormatter("%d")
        #
        # ax.xaxis.set_major_locator(mondays)
        # ax.xaxis.set_minor_locator(alldays)
        # ax.xaxis.set_major_formatter(weekFormatter)
        #
        # candlestick2_ohlc(ax, ndf['open'], ndf['high'], ndf['low'], ndf['close'], width=1, colorup='r', colordown='b')
        #
        # ax.xaxis_date()
        # ax.autoscale_view()
        #
        # axpos = ax
        # spos = Slider(axpos, 'Position', dt.date(dt.now() - datetime.timedelta(days=7)).toordinal(), dt.date(dt.now()).toordinal())
        #
        # def update(val):
        #     pos = spos.val
        #     ax.axis([pos, pos + 10, 18.5, 22.5])
        #     self.canvas.draw_idle()
        #
        # spos.on_changed(update)

        ax.plot(ndf['date'], ndf['close'].rolling(window=5).mean(), label="5", linewidth=0.7)
        ax.plot(ndf['date'], ndf['close'].rolling(window=20).mean(), label="20", linewidth=0.7)
        ax.plot(ndf['date'], ndf['close'].rolling(window=60).mean(), label="60", linewidth=0.7)
        ax.plot(ndf['date'], ndf['close'].rolling(window=120).mean(), label="120", linewidth=0.7)
        candlestick2_ohlc(ax, ndf['open'], ndf['high'], ndf['low'], ndf['close'], width=1, colorup='r', colordown='b')

        self.fig.suptitle("candle")
        ax.set_xlabel("date")
        ax.set_ylabel("stock price")

        # ax.tick_params(axis='x', labelrotation=20)
        ax.autoscale_view()

        ax.xaxis.set_major_locator(ticker.MaxNLocator(5))
        ax.legend(loc=1) # legend 위치
        self.canvas.draw()

    def learnFunc(self):
        if self.code is None:
            return
        # 데이터 전처리
        code = self.code
        chart_data = self.df
        prep_data = data_manager.preprocess(chart_data)
        training_data = data_manager.build_training_data(prep_data)
        training_data = training_data.dropna()

        # 차트데이터 분리
        feature_chart_data = ['date', 'open', 'high', 'low', 'close', 'volume']
        chart_data = training_data[feature_chart_data]

        # 학습데이터 분리
        feature_chart_data = [
            'open_lastclose_ratio','high_close_ratio','low_close_ratio',
            'close_lastclose_ratio','volume_lastvolume_ratio',
            'close_ma5_ratio','volume_ma5_ratio',
            'close_ma10_ratio', 'volume_ma10_ratio',
            'close_ma20_ratio', 'volume_ma20_ratio',
            'close_ma60_ratio', 'volume_ma60_ratio',
            'close_ma120_ratio', 'volume_ma120_ratio',
        ]
        training_data = training_data[feature_chart_data]


        # 정책 신경망을 파일로 저장
        self.createFolder('model')
        mdir = os.path.join(settings.BASE_DIR, 'model')
        self.createFolder(os.path.join(mdir, code))

        model_dir = os.path.join(mdir, code)
        model_path = os.path.join(model_dir, 'model%s.h5' %(code))

        if model_path is None:
            start_time = time.time()
            policy_learner = PolicyLearner(
                stock_code=code,
                chart_data=chart_data,
                training_data=training_data,
                fig=self.fig,
                canvas=self.canvas,
                min_trading_unit=1,
                max_trading_unit=2,
                delayed_reward_threshold=0.2,
                lr=0.001)
            policy_learner.fit(
                balance=10000000,
                num_epoches=200,
                discount_factor=0,
                start_epsilon=0.5)
            end_time = time.time()
            policy_learner.policy_network.save_model(model_path)
            print("LearningTime: {} sec".format(end_time - start_time))
        else:
            start_time = time.time()
            policy_learner = PolicyLearner(
                stock_code=code,
                chart_data=chart_data,
                training_data=training_data,
                fig=self.fig,
                canvas=self.canvas,
                min_trading_unit=1,
                max_trading_unit=2)
            end_time = time.time()
            print("LearningTime: {} sec".format(end_time - start_time))
            policy_learner.trade(balance=1000000,
                                 model_path=os.path.join(model_dir, 'model%s.h5'%(code)))

    def createFolder(self, directory):
        try:
            if not os.path.isdir(os.path.join(settings.BASE_DIR, directory)):
                os.mkdir(os.path.join(settings.BASE_DIR, directory))
        except OSError:
            print('ERR\t:\tFail to make directory "'+directory+'"')