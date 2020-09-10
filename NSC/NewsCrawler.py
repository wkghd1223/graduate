import requests
from bs4 import BeautifulSoup
import pandas as pd
from datetime import datetime
import time
import multiprocessing

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''
< naver 뉴스 전문 가져오기 >_select 사용
- 네이버 뉴스만 가져와서 결과값 조금 작음 
- 결과 메모장 저장 -> 엑셀로 저장 
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#
#
# def get_count(num, p=4):
#     list = []
#     allocate = int(num / p)
#     for n in range(p):
#         list.append(allocate)
#     list[p - 1] += num % p
#     print("프로세스당 할당량: ", list)
#     return list


class crawling:
    def __init__(self, maxpage, query, s_date, e_date):
        self.maxpage = maxpage
        self.query = query
        self.s_date = s_date
        self.e_date = e_date

    def crawler(self, maxpage, query, s_date, e_date):
        result = []
        # 네이버 뉴스 홈에 등록된 기사인지 확인후 맞으면 해당 url을 get_news에 보내고 리턴값(리스트 형식)을 메모장으로 저장
        s_from = self.s_date.replace("-", "")  # 우측부터 "."을 찾아서 ""으로 바꿈
        e_to = self.e_date.replace("-", "")  # 우측부터 "."을 찾아서 ""으로 바꿈
        page = 1
        maxpage_t = (int(self.maxpage) - 1) * 10 + 1  # 11= 2페이지 21=3페이지 31=4페이지  ...81=9페이지 , 91=10페이지, 101=11페이지

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
                    if urls["href"].startswith("https://news.naver.com"):
                        news_detail = self.get_news(urls["href"])
                        if news_detail is not None:
                            result.append(news_detail)

                except Exception as e:
                    print(e)
                    continue
            page += 10
        # time.sleep(1)
        return result

    def get_news(self, n_url):
        news_detail = []  # crawler 함수로부터 n_url을 받아서 크롤링해 리턴할 list형태의 데이터
        try:
            breq = requests.get(n_url, timeout=1)
        except Exception as e:
            print(e)
            return None

        bsoup = BeautifulSoup(breq.content, 'html.parser')

        pdate = bsoup.select('.t11')[0].get_text()[:11]
        news_detail.append(pdate)

        title = bsoup.select('h3#articleTitle')[0].text  # 대괄호는  h3#articleTitle 인 것중 첫번째 그룹만 가져오겠다.
        news_detail.append(title)

        pcompany = bsoup.select('#footer address')[0].a.get_text()
        news_detail.append(pcompany)

        # _text = bsoup.select('#articleBodyContents')[0].get_text().replace('\n', " ")
        # btext = _text.replace("// flash 오류를 우회하기 위한 함수 추가 function _flash_removeCallback() {}", "")
        # news_detail.append(btext.strip())

        news_detail.append(n_url)

        return news_detail


if __name__ == "__main__":
    maxpage = 10
    process = []
    c = crawling(maxpage, '애플', '2020-09-06', '2020-09-07')
    start = time.time()
    c.crawler(maxpage, '삼성', '2019-09-07', '2020-09-08')
    # for count in get_count(maxpage, 4):
    #     p = multiprocessing.Process(target=c.crawler, args=(count, '애플', '2020-09-06', '2020-09-07'))
    #     process.append(p)
    #     p.start()
    #
    # for p in process:
    #     p.join()
    print("소요 시간: ", round(time.time() - start, 6))
