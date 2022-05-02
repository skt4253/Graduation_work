# Graduation Work

## Posture correction system

### 2022-04-23
- 3월 작업 내용은 따로 백업함.

<br/>

--- 
### 2022-03-31
- 기본적인 웹 페이지 제작, 주석 작성 완료

- 다음 작업에서는 js로 실시간 이미지 변경, 문구 수정 기능 업데이트
- js로 바른 자세에 대한 페이지를 접기/펼치기가 가능하도록 업데이트

* 다음 작업은 일요일까지 작업 후, 카페에 작업 요약본 업로드 예정

<br />

---
### 2022-04-03
HARDWARE(Posture_correction(ver.8))
- 모비우스에 값 전달하는 것 아직 진행중

<br />

---
### 2022-04-08
HARDWARE(Posture_correction(ver.9))
- 센서값이 PHP를 통해 DB에 저장될 수 있도록 함

<br />

---
### 2022-04-10
- 바른 자세란?의 페이지 접기/펼치기 기능 추가
- **코드는 HTML branch를 따로 생성해 업로드함. 이제 바로 html 코드 확인 가능**
<br/>

1. 센서값이 DB에 저장이 가능해졌으므로, DB에서 데이터를 받아오는 코드 추가 예정
2. 머신러닝 모델을 추가할 수 있는 Tensorflow.js 공부 중
3. js를 사용하여 실시간으로 이미지/문구가 변경될 수 있는 코드 작성 예정
- 시험 기간 내에 최대한 끝내볼 예정

<br />

---
### 2022-04-23
- 티처블 머신으로 상체를 판단하는 머신러닝 모델 제작, HTML에 삽입 완료 -> 이 부분을 하게 된다면 모델에 샘플을 더 추가하여 완성도를 올릴 예정임.
- 현재는 음성으로 알려주는 상태 (좌우가 반전돼서 음성이 나오는데, 이는 곧 수정할 예정)
- 현재(4월 23일 오후 6시 30분)까지 제작한 코드와 기타 파일들을 업로드함.

<br />

---
### 2022-04-29
#### HARDWARE
machine learning.zip: 제가 가지고 있던 데이터로 돌려본 머신러닝<br>
sensor.php: DB에 저장했던 값 불러오는 

---
### 2022-05-02
#### HARDWARE (machine learning(ver.2))
- 입력값을 입력시 저장되어있는 머신러닝을 불러와 예측한 뒤 웹페이지에 나타나도록 함<br>
- DB와 연결하여 입력값을 DB에서 가져온 값으로 처리할 예정
- 사용방법과 참고자료: 1. https://velog.io/@awesome-hong/VScode%EC%97%90%EC%84%9C-%EA%B0%80%EC%83%81%ED%99%98%EA%B2%BD-%EC%84%A4%EC%A0%95-Flask-%EC%84%A4%EC%B9%98%ED%95%98%EA%B8%B0<br>
                     2. https://abluesnake.tistory.com/106
