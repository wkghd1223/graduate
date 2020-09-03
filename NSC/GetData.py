import pandas as pd
import plotly.offline as offline
import plotly.graph_objs as go

# 한국거래소(krx)에서 주식시장에 상장된 기업들에 대해 종목코드 가져오기
code_df = pd.read_html('http://kind.krx.co.kr/corpgeneral/corpList.do?method=download&searchType=13', header=0)[0]

# 종목코드가 6자리이기 때문에 6자리 맞춰주는 설정
code_df.종목코드 = code_df.종목코드.map('{:06d}'.format)

# 필요한 회사명, 종목코드 컬럼이외 필요없는 컬럼제외
code_df = code_df[['회사명', '종목코드']]

# 한글로된 컬럼명을 영어로 바꾸기
code_df = code_df.rename(columns={'회사명': 'name', '종목코드': 'code'})

# 상위 5개의 코드 확인
code_df.head()

# 종목이름 입력하면 종목에 해당하는 코드를 불러와 네이버 금융(http://finance.naver.com)에 넣어줌
def get_url(item_name, code_df):
    code = code_df.query("name=='{}'".format(item_name))['code'].to_string(index=False)
    code = code.strip()
    url = 'http://finance.naver.com/item/sise_day.nhn?code={code}'.format(code=code)

    print("요청 URL = {}".format(url))
    return url

# 종목이름의 일자데이터 url 가져오기
item_name = '삼성전자'
url = get_url(item_name, code_df)

# 일자 데이터를 담을 df라는 DataFrame 정의
df = pd.DataFrame()

# 1페이지에서 20페이지의 데이터만 가져오기
for page in range(1, 21):
    pg_url = '{url}&page={page}'.format(url=url, page=page)
    df = df.append(pd.read_html(pg_url, header=0)[0], ignore_index=True)
    df = df.append(pd.read_html(pg_url, header=0)[0], ignore_index=True)

# df.dropna()를 이용해 결측값 있는 행 제거
df = df.dropna()

# 상위 5개 데이터 확인하기
df.head()

df = df.rename(columns={
    '날짜': 'date', '종가': 'close', '전일비': 'diff', '시가': 'open', '고가': 'high', '저가': 'low', '거래량': 'volume'
})
df[['close', 'diff', 'open', 'high', 'low', 'volume']] \
    = df[['close', 'diff', 'open', 'high', 'low', 'volume']].astype(int)
df['date'] = pd.to_datetime(df['date'])
df = df.sort_values(by=['date'], ascending=True)
df.head()

# offline.init_notebook_mode(connected=True)

trace = go.Scatter(
    x=df.date,
    y=df.close,
    name=item_name
)
data = [trace]

layout = dict(
    title='{}의 종가(close) Time Series'.format(item_name),
    xaxis=dict(
        rangeselector = dict(
            buttons=list([
                dict(count=1,
                     label='1m',
                     step='month',
                     stepmode='backward'
                     ),
                dict(count=3,
                     label='3m',
                     step='month',
                     stepmode='backward'
                     ),
                dict(count=6,
                     label='6m',
                     step='month',
                     stepmode='backward'
                     ),
                dict(step='all'
                     ),
            ])
        ),
        rangeslider=dict(),
        type='date'
    )
)
fig = go.Figure(data=data, layout=layout)
offline.plot(fig)
