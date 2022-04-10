# Graduation Work

## Posture correction system

### 2022-03-19
- 2월 작업 내용은 따로 백업함.

<br/>

1. 아이디 중복 확인을 누르면 php파일이 다운로드되는 현상은 xampp 내에 있는 conf파일을 수정하면 현상을 해결할 수 있을 것 같음. 근데 코드를 수정해서 실행하니 블루스크린이 떠버려서 함부로 수정하면 안 될 것 같음.... 일단 서칭은 계속 하고 있지만, 해결이 안 되면 다른 프로그램을 사용할 예정임.
2. 회원가입 폼에서 가입하기 버튼을 누르면 유효성 검사가 실행되게 수정함. DB에 업데이트가 되려면 위의 문제를 해결해야 가능할 것으로 보임.

---

- 코드를 수정하면 자꾸 블루 스크린이 떠서 일단 백업해놓은 코드를 업로드하겠습니다. 블루 스크린 오류는 화~수까지 해결하고, 남은 작업을 쭉 진행할 예정임.

---
### 2022-03-20
하드웨어(Posture_correction(ver.7))
- DB에 센서 값이 들어가기는 함. 하지만 갑이 0만 들어가고 있는 상황이어서 해결해 보도록 하겠습니다.

---
### 2022-03-25
1. 결과 보고서 작성에 사용할 근거 자료 수집 중임. 현재 학술 논문을 확인했고, 우리 졸작에 나름 도움이 될 만한 학술 논문은 카페에 업로드함.
2. 현재 석, 박사 논문과 의학 서적을 확인 중임. 이것들의 양이 많아 이 부분은 토요일 저녁 전까지 간략하게 정리해서 업로드를 할 예정임.
---
HARDWARE
- DB에 값이 0만 들어가는 이유가 전송할 때 바이트 수 때문에 그런 것 같습니다. 
  센서 값 10개까지 보냈을 때는 잘 보내졌는데 그 이상의 센서 값을 보내려고 하니까 겂이 0만 보내지거나 오류가 났습니다.
- 모비우스 사용하려고 nCube-Thyme-Arduino 찾아보고 있는데 정보가 많이 없음,,ㅠ(Help me)
- 보고서 쓸 때 필요할 수 있으니까 카페에 방석 센서 자료 올려놓겠습니다. 

--- 
### 2022-03-29
HARDWARE(dataset)
- 센서 값을 엑셀파일에 저장할 수 있도록 함.
- 사용 방법은 카페에 업로드

--- 
### 2022-03-31
- 기본적인 웹 페이지 제작, 주석 작성 완료

- 다음 작업에서는 js로 실시간 이미지 변경, 문구 수정 기능 업데이트
- js로 바른 자세에 대한 페이지를 접기/펼치기가 가능하도록 업데이트

* 다음 작업은 일요일까지 작업 후, 카페에 작업 요약본 업로드 예정
---

### 2022-04-03
HARDWARE(Posture_correction(ver.8))
- 모비우스에 값 전달하는 것 아직 진행중

---
### 2022-04-08
HARDWARE(Posture_correction(ver.9))
- 센서값이 PHP를 통해 DB에 저장될 수 있도록 함

---
### 2022-04-10
- 바른 자세란?의 페이지 접기/펼치기 기능 추가
**- 코드는 HTML branch를 따로 생성해 업로드함. 이제 바로 html 코드 확인 가능**
<br/>

1. 센서값이 DB에 저장이 가능해졌으므로, DB에서 데이터를 받아오는 코드 추가 예정
2. 머신러닝 모델을 추가할 수 있는 Tensorflow.js 공부 중
3. js를 사용하여 실시간으로 이미지/문구가 변경될 수 있는 코드 작성 예정
- 시험 기간 내에 최대한 끝내볼 예정
