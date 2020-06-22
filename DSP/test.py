import tensorflow as tf
from tensorflow import keras
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
import os


# dataset을 만들어 주는 함수
# label : 결과
# feature : 입력값
# window_size : 과거 몇일을 기반으로 예측 할 것인가에 대한 변수
def make_dataset(data, label, window_size=90):
    feature_list = []
    label_list = []
    for i in range(len(data) - window_size):
        feature_list.append(np.array(data.iloc[i:i+window_size]))
        label_list.append(np.array(label.iloc[i+window_size]))
    return np.array(feature_list), np.array(label_list)


data_path = r'./'
model_path = r'./'
df_price = pd.read_csv(os.path.join(data_path, 'samsung_ko.csv'), encoding='utf8')
# print(df_price.describe())

df_price['일자'] = pd.to_datetime(df_price['일자'], format='%Y%m%d')
df_price['연도'] = df_price['일자'].dt.year
df_price['월'] = df_price['일자'].dt.month
df_price['일'] = df_price['일자'].dt.day

df = df_price.loc[df_price['연도'] >= 1990]

plt.figure(figsize=(16, 9))
sns.lineplot(y=df['종가'], x=df['일자'])
plt.xlabel('time')
plt.ylabel('price')
# plt.legend()
# plt.show()
scaler = MinMaxScaler()
scale_cols = ['시가', '고가', '저가', '종가', '거래량']
df_scaled = scaler.fit_transform(df[scale_cols])

df_scaled = pd.DataFrame(df_scaled)
df_scaled.columns = scale_cols

# print(df_scaled)

TEST_SIZE = 200
train = df_scaled[:-TEST_SIZE]
test = df_scaled[-TEST_SIZE:]

# feature / label 정의
feature_cols = ['시가', '고가', '저가', '거래량']
label_col = ['종가']

train_feature = train[feature_cols]
train_label = train[label_col]

# train dataset
train_feature, train_label = make_dataset(train_feature, train_label)

# train, validation set 생성
x_train, x_valid, y_train, y_valid = train_test_split(train_feature, train_label, test_size=0.2)

print(x_train.shape, x_valid.shape)

# 실제 예측 데이터
test_feature = test[feature_cols]
test_label = test[label_col]

test_feature, test_label = make_dataset(test_feature, test_label)
print(test_feature.shape, test_label.shape)

# 모델 생성
model = keras.Sequential()
model.add(keras.layers.LSTM(16,
                            input_shape=(train_feature.shape[1], train_feature.shape[2]),
                            activation='relu',
                            return_sequences=False)
          )
model.add(keras.layers.Dense(1))
#
# # 학습
#
# # 가장 많이 쓰이는 optimizer
# # optimizer = keras.optimizers.Adam(0.01)
# model.compile(loss='mean_squared_error', optimizer='adam')
# # 더 이상의 학습으로 성능이 좋아지지 않을 때 사용한다.
# # monitor = 'val_loss' : validation set 의 loss 를 monitoring 한다는 뜻
# # patience = 5 : 성능이 증가하지 않는 epoch 를 5번 허용
# # verbose : 콘솔창에 출력
# early_stop = keras.callbacks.EarlyStopping(monitor='val_loss', patience=5)
filename = os.path.join(model_path, 'temp_checkpoint.h5')
# # mode = 'auto' : 값을 최소화 하는 방향으로 갈 지 최대화 하는 방향으로 갈 지 알아서 선택
# checkpoint = keras.callbacks.ModelCheckpoint(filename, monitor='val_loss', verbose=1, save_best_only=True, mode='auto')
#
# history = model.fit(x_train, y_train,
#                     epochs=200,
#                     batch_size=16,
#                     validation_data=(x_valid, y_valid),
#                     callbacks=[early_stop, checkpoint])

# 미래 예측

# weigh 로딩
model.load_weights(filename)

# 예측
predict = model.predict(test_feature)
print(predict)
#
plt.figure(figsize=(12, 9))
plt.plot(test_label, label='actual')
plt.plot(predict, label='prediction')
plt.legend()
plt.show()