import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import uic
from NewsCrawler import *


class NewsWindowClass(QmainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)