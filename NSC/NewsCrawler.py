import requests
from bs4 import BeautifulSoup
import pandas as pd
from datetime import datetime

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''
< naver 뉴스 전문 가져오기 >_select 사용
- 네이버 뉴스만 가져와서 결과값 조금 작음 
- 결과 메모장 저장 -> 엑셀로 저장 
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''
# 메모장 및 엑셀 파일 저장 경로
RESULT_PATH = 'C:/Users/USER/Desktop/백욱진/졸프_주분투/graduate/NSC/crawledNews/'
now = datetime.now()  # 파일이름 현 시간으로 저장하기


def get_news(n_url):
    news_detail = []  # crawler 함수로부터 n_url을 받아서 크롤링해 리턴할 list형태의 데이터

    breq = requests.get(n_url)
    bsoup = BeautifulSoup(breq.content, 'html.parser')

    title = bsoup.select('h3#articleTitle')[0].text  # 대괄호는  h3#articleTitle 인 것중 첫번째 그룹만 가져오겠다.
    news_detail.append(title)

    pdate = bsoup.select('.t11')[0].get_text()[:11]
    news_detail.append(pdate)

    _text = bsoup.select('#articleBodyContents')[0].get_text().replace('\n', " ")
    btext = _text.replace("// flash 오류를 우회하기 위한 함수 추가 function _flash_removeCallback() {}", "")
    news_detail.append(btext.strip())

    news_detail.append(n_url)

    pcompany = bsoup.select('#footer address')[0].a.get_text()
    news_detail.append(pcompany)

    return news_detail


class crawling:
    def __init__(self, maxpage, query, s_date, e_date):
        self.maxpage = maxpage
        self.query = query
        self.s_date = s_date
        self.e_date = e_date

    def crawler(self, maxpage, query, s_date, e_date):

        # 네이버 뉴스 홈에 등록된 기사인지 확인후 맞으면 해당 url을 get_news에 보내고 리턴값(리스트 형식)을 메모장으로 저장
        s_from = self.s_date.replace(".", "")  # 우측부터 "."을 찾아서 ""으로 바꿈
        e_to = self.e_date.replace(".", "")  # 우측부터 "."을 찾아서 ""으로 바꿈
        page = 1
        maxpage_t = (int(self.maxpage) - 1) * 10 + 1  # 11= 2페이지 21=3페이지 31=4페이지  ...81=9페이지 , 91=10페이지, 101=11페이지
        f = open("C:/Users/USER/Desktop/백욱진/졸프_주분투/graduate/NSC/crawledNews/crawling_result.txt", 'w',
                 encoding='utf-8')  # open(파일 이름, 파일 열기모드 w=쓰기모드)

        while page < maxpage_t:  # page가 maxpage_t보다 작을 동안

            print(page)

            url = "https://search.naver.com/search.naver?where=news&query=" + self.query + "&sort=0&ds=" + self.s_date + "&de=" + self.e_date + "&nso=so%3Ar%2Cp%3Afrom" + s_from + "to" + e_to + "%2Ca%3A&start=" + str(
                page)

            req = requests.get(url)
            print(url)
            cont = req.content
            soup = BeautifulSoup(cont, 'html.parser')
            # print(soup)

            for urls in soup.select("._sp_each_url"):  # '_sp_each_url'은 네이버뉴스로 가는 하이퍼링크가 걸린 부분의 클래스명
                try:
                    # print(urls["href"])
                    if urls["href"].startswith("https://news.naver.com"):
                        # print(urls["href"])
                        news_detail = get_news(urls["href"])
                        # pdate, pcompany, title, btext
                        f.write("{}\t{}\t{}\t{}\t{}\n".format(news_detail[1], news_detail[4], news_detail[0],
                                                              news_detail[2], news_detail[3]))  # new style
                except Exception as e:
                    print(e)
                    continue
            page += 10

        f.close()

    def excel_make(self):
        data = pd.read_csv(RESULT_PATH + 'crawling_result.txt', sep='\t', header=None, error_bad_lines=False)
        data.columns = ['years', 'company', 'title', 'contents', 'link']
        print(data)

        xlsx_outputFileName = '%s-%s-%s  %s시 %s분 %s초 result.xlsx' % (
            now.year, now.month, now.day, now.hour, now.minute, now.second)
        xlsx_name = 'result' + '.xlsx'
        data.to_excel(RESULT_PATH + xlsx_outputFileName, encoding='utf-8')


def main():  # 사용자로부터 입력 값 받아서 crawler함수 넘겨주고 엑셀로 만들라는 지시
    maxpage = input("최대 출력할 페이지수 입력하시오: ")
    query = input("검색어 입력: ")
    s_date = input("시작날짜 입력(2019.01.01):")  # 2019.01.01
    e_date = input("끝날짜 입력(2019.04.28):")  # 2019.04.28
    c = crawling(maxpage, query, s_date, e_date)
    c.crawler(maxpage, query, s_date, e_date)  # 검색된 네이버뉴스의 기사내용을 크롤링합니다.
    c.excel_make()  # 엑셀로 만들기


main()
