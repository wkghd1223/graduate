# Tensorflow 예제 가이드

## 1. Virtualenv 다운로드

가상환경 설정
https://virtualenv.pypa.io/en/stable/user_guide.html 참고하며 설정

virtualenv 다운로드
```bash
$ python -m pip install virtualenv
```
가상환경 설정
```bash
$ python -m virtualenv venv
```
가상환경 실행
```bash
$ source ./Scripts/activate
(venv) $
```
몇 번의 시행착오를 겪으며 Jubuntu라는 이름의 가상환경을 구축하였음
```bash
$ python -m venv Jubuntu
```

## Tensorflow 설치
python 3.8.x로 tensorflow가 다운로드가 안되서 python3.7.7버전으로 다운받았음

```bash
$ pip install tensorflow
ERROR: Could not find a version that satisfies the requirement tensorflow (from versions: none)
ERROR: No matching distribution found for tensorflow
```
64비트 버전이 없어서 python3.7.5 x84-64버전 을 다시 받았음
```bash
$ python --version
Python 3.7.5
$ pip install tensorflow
```
잘 설치 되었는 지 결과 확인
```python
import tensorflow as tf
print(tf.__version__)
```
```
2020-05-16 22:21:53.819477: W tensorflow/stream_executor/platform/default/dso_loader.cc:55] Could not load dynamic library 'cudart64_101.dll'; dlerror: cudart64_101.dll not found
2020-05-16 22:21:53.819599: I tensorflow/stream_executor/cuda/cudart_stub.cc:29] Ignore above cudart dlerror if you do not have a GPU set up on your machine.
2.2.0
```
## 주요 라이브러리 설치
주요라이브러리 tensorflow와 더불어 사용되는 주요 라이브러리를 설치한다.

1. `numpy`

    고성능 수치 계산용 라이브러리. 텐서플로우 설치하면 자동으로 깔린다.

1. `pandas`(Python Data Analysis Library)
    
    데이터 문석 모듈이다.
    ```bash
    $ pip install pandas
    ```
    ```python
    import pandas as pd
    ```
    csv파일 가져오기, 테이블 형식으로 데이터 만들기 등의 역할을 한다.

1. `matplotlib`

    데이터를 차트나 플롯으로 그려주는 라이브러리이다.
    ```bash
    $ pip install matplotlib
    ```
    ```python
    from matplotlib import pyplot as plt
    # 또는
    import matplotlib.pyplot as plt
    ```

1. `seaborn`

    통계 그래프를 그리는 라이브러리이다. matplotlib에 종속성을 가지고 있다.
    ```bash
    $ pip install scikit-learn
    # 또는
    $ pip install seaborn
    ```

## 구현

```python
import tensorflow as tf
from tensorflow import keras
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
import os
```

```python
# dataset을 만들어 주는 함수
# label : 결과
# feature : 입력값
# window_size : 과거 몇일을 기반으로 예측 할 것인가에 대한 변수
def make_dataset(data, label, window_size=20):
    feature_list = []
    label_list = []
    for i in range(len(data) - window_size):
        feature_list.append(np.array(data.iloc[i:i+window_size]))
        label_list.append(np.array(label.iloc[i+window_size]))
    return np.array(feature_list), np.array(label_list)
```
pandas라이브러리를 이용하여 .csv 형식의 파일을 가져왔다.
```python
data_path = r'./'
model_path = r'./'
df_price = pd.read_csv(os.path.join(data_path, 'samsung_ko.csv'), encoding='utf8')
print(df_price.describe())
```

_결과값_
```bash
                일자          시가  ...          종가         거래량
count  9.288000e+03   9288.000000  ...   9288.000000  9.288000e+03
mean   2.001347e+07  11108.556417  ...  11108.235465  1.645823e+07
std    1.015376e+05  13792.646300  ...  13790.922497  1.701535e+07
min    1.985010e+07    116.000000  ...    116.000000  0.000000e+00
25%    1.992121e+07    624.000000  ...    623.000000  3.833986e+06
50%    2.001032e+07   5045.000000  ...   5075.000000  1.199608e+07
75%    2.010080e+07  15920.000000  ...  15920.000000  2.284080e+07
max    2.020011e+07  57500.000000  ...  57220.000000  3.266220e+08
```

```python
# 일자 데이터를 년도, 월, 일로 나눈다.
df_price['일자'] = pd.to_datetime(df_price['일자'], format='%Y%m%d')
df_price['연도'] = df_price['일자'].dt.year
df_price['월'] = df_price['일자'].dt.month
df_price['일'] = df_price['일자'].dt.day

# loc() 함수를 통해 년도가 1990년 이상인 데이터만 인덱싱을 하도록 한다.
df = df_price.loc[df_price['연도'] >= 1990]

# matplotlib를 이용하여 주가의 1990년도 이후의 값을 그래프로 나타낸다.
plt.figure(figsize=(16, 9))
sns.lineplot(y=df['종가'], x=df['일자'])
plt.xlabel('time')
plt.ylabel('price')
plt.legend()
plt.show()

# MinMaxScaler로 0 ~ 1의 값을 갖게 한다.
scaler = MinMaxScaler()
scale_cols = ['시가', '고가', '저가', '종가', '거래량']
# fit() 메소드는 데이터 변환을 학습
# transform() 메소드는 실제 데이터의 스케일을 조정함
# scaler는 단축 메소드인 fit_transform()를 제공함
# fit() 은 학습용 데이터에만 적용해야 함
# 따라서 테스트 데이터는 transform()함수만 적용
df_scaled = scaler.fit_transform(df[scale_cols])

# 2차원 배열의 테이블 형태로 데이터를 정규화 해줌
df_scaled = pd.DataFrame(df_scaled)
df_scaled.columns = scale_cols

print(df_scaled)
```

_결과값_

![stock_samsung](./Figure_1.png)
```bash
시가        고가        저가        종가       거래량
0     0.968482  0.980394  0.979423  0.975012  0.030291
1     0.954474  0.966389  0.961684  0.969733  0.031470
2     0.973735  0.983895  0.967005  0.969733  0.047217
3     0.964980  0.973391  0.968779  0.964454  0.039781
4     0.977237  0.983895  0.981197  0.975012  0.025585
...        ...       ...       ...       ...       ...
7823  0.005095  0.005094  0.005073  0.004927  0.002960
7824  0.005165  0.005129  0.005215  0.005068  0.005279
7825  0.005236  0.005199  0.005162  0.005015  0.005483
7826  0.005236  0.005339  0.005286  0.005279  0.008384
7827  0.004955  0.005129  0.004860  0.005138  0.005251
```
학습데이터셋과 테스트 할 데이터셋을 생성한다.
```python
TEST_SIZE = 200
train = df_scaled[:-TEST_SIZE]
test = df_scaled[-TEST_SIZE:]

# feature / label 정의
feature_cols = ['시가', '고가', '저가', '거래량']
label_col = ['종가']

train_feature = train[feature_cols]
train_label = train[label_col]

# train dataset
train_feature, train_label = make_dataset(train_feature, train_label, 20)

# train, validation set 생성
x_train, x_valid, y_train, y_valid = train_test_split(train_feature, train_label, test_size=0.2)

print(x_train.shape, x_valid.shape)

# 실제 예측 데이터
test_feature = test[feature_cols]
test_label = test[label_col]

test_feature, test_label = make_dataset(test_feature, test_label, 20)
print(test_feature.shape, test_label.shape)
```
_결과값_
```bash
(6086, 20, 4) (1522, 20, 4)
(180, 20, 4) (180, 1)
```

학습 모델을 만들고 학습시키고 테스트한다.
```python
# 모델 생성
model = keras.Sequential()
model.add(keras.layers.LSTM(16,
                            input_shape=(train_feature.shape[1], train_feature.shape[2]),
                            activation='relu',
                            return_sequences=False)
          )
model.add(keras.layers.Dense(1))

# 학습

# optimizer = keras.optimizers.Adam(0.01)
model.compile(loss='mean_squared_error', optimizer='adam')
early_stop = keras.callbacks.EarlyStopping(monitor='val_loss', patience=5)
filename = os.path.join(model_path, 'temp_checkpoint.h5')
checkpoint = keras.callbacks.ModelCheckpoint(filename, monitor='val_loss', verbose=1, save_best_only=True, mode='auto')

history = model.fit(x_train, y_train,
                    epochs=200,
                    batch_size=16,
                    validation_data=(x_valid, y_valid),
                    callbacks=[early_stop, checkpoint])

# 미래 예측

# weigh 로딩
model.load_weights(filename)

# 예측
predict = model.predict(test_feature)

plt.figure(figsize=(12, 9))
plt.plot(test_label, label='actual')
plt.plot(predict, label='prediction')
plt.legend()
plt.show()
```
![stock_samsung_predict](./Figure_2.png)
