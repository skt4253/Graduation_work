# Graduation Work

## Posture correction system

<br/>

### 2022-01-08
데이터베이스는 localhost로 실행하기 때문에 아래의 프로그램을 다운로드해야함.

XAMPP control panel: https://www.apachefriends.org/download.html

위의 프로그램을 실행하고, "Apache"와 "MySQL"을 Start해야함. ("MySQL"을 실행 시, 가끔 충돌이 일어나는 오류가 있음.)

1. Visual Studio Code를 사용 시, 확장 프로그램인 "Live Server Web Extension" 설치
2. 서버와 데이터베이스는 PHP를 사용하므로, php 확장 프로그램 설치
3. localhost로 실행되기 때문에 각자 데이터베이스를 만들어야 함.
4. XAMPP control panel를 실행하고, 크롬에서 127.0.0.1를 입력
5. 오른쪽 상단에 MyPHPAdmin 클릭
6. 테이블을 생성하고, 압축 파일에 있는 "members" 파일을 실행 (이 방법은 글로 쓰기가 어려워서 추후에 말로 설명할 예정)

### 서버와 데이터베이스에 대한 설명은 추후 설명할 예정

#### 일단 사용자 추가, 삭제, 업데이트, 로그인이 가능한 웹 페이지를 제작해야함.

<br/>

---
### 2022-01-10
하드웨어(아두이노 코드 Posture correction(ver.1))
- 압력센서, 진동센서 사용하는 코드(완전 완성은 x)

<br/>

---
### 2022-01-15
DB의 CRUD는 구현을 하였으나, 회원 가입 시 아이디 중복 체크 기능에서 오류가 발생하여 수정함. 그러나, 오류가 계속되어 일단 이 상태로 업로드하였고, 추후 수정 예정
#### php 코드는 'C:/xampp/htdocs(기본적으로 설치되는 주소이므로, 각자 설치된 주소 밑의 xampp/htdocs(앞의 폴더 이름은 똑같음) 폴더 안에 넣고, 주소를 입력하여 실행 가능) 

추신: DB ver.2에 있는 img 폴더 안에 우리집 멍멍이 사진을 실수로 같이 넣었는데, 귀찮아서 걍 넣습니다...ㅋㅋㅋㅋ 즐거운(?) 구경하세요~

<br/>

---
### 2022-01-16
하드웨어(아두이노 코드 Posture correction(ver.1.1))
- 아두이노 우노로 시리얼 모니터에 값이 나올 수 있도록 수정
- 시리얼 모니터에 값이 바로바로 나오는 것이 아니라 3초있다가 나올 수 있도록 수정
- 하드웨어는 완성
- 압력센서랑 진동센서를 따로 실행해 보면 작동하는데 같이 실행하면 안되고 있음,,,

<br/>

---
### 2022-01-22
일, 주, 월 데이터를 저장하는 DB 생성
일(dayCount): 하루동안의 누적 시간을 저장하는 방식으로, 시간 저장 공간이 1개 -> 타이머에서 누적 시간이 출력될 때 사용
주(weeks): 월~일까지의 시간을 저장하므로, 저장 공간이 7개
월(months): 현재 달부터 지난 3개월 전까지의 누적 시간을 저장, 저장 공간이 4개

회원 가입 폼에서 회원 가입을 할 경우, members 테이블에 저장되는 동시에 고유 아이디가 시간을 저장하는 테이블과 그룹 지정 테이블에 등록됨.
#### 현재 그룹 지정은 3개까지 가능함. (구체적인 방법은 구현이 안 됐지만, 나중에 그룹을 생성하면 그룹 이름이 DB에 저장하는 방식을 차용하려 함.) 

그리고, 바른 자세와 티쳐블 머신에 대해 조사하려고 했지만, 이번 주에 좀... 바빴어서 자료 조사를 제대로 못했습니다. 일단 회의 전까지는 할 테지만 자료 조사를 다음 주까지로 늘려야할 것 같습니다...ㅜㅜ

#### +) 현재 회원 탈퇴(delete) 폼은 로그인된 상태에서 진행해야 하는데 로그인 기능 연결은 홈페이지가 얼추 만들어지면 로그인 기능을 추가할 예정이므로, 회원 탈퇴는 오류가 생기는 게 정상입니다.

<br/>

--- 
### 2022-01-23
하드웨어(아두이노 코드 Posture correction(ver.2))
- 자세가 왼쪽으로 기울었을 때와 오른쪽으로 기울었을 때 진동센서가 울릴 수 있도록 했습니다.

<br/>

--- 
### 2022-01-30
1. DB에 EU타임을 저장할 수 있는 공간을 추가함.
2. 회원가입 요소에서 '생년월일'을 추가할 수 있는 DB 공간은 마련했지만, 아직 코드에 작성하지는 못함. 
3. 현재 바른 앉는 자세를 알아봤고, 추후 더 많은 근거 자료와 스트레칭 자세를 조사할 예정임.
4. 티쳐블 머신을 조사한 바에 의하면, 아두이노에서도 작동 가능하지만, 캠이나 마이크 같은 기능으로만 작동이 가능한 것으로 보임. 우리 작품은 코드 내부에서 작동해야 하니 따라서, 티쳐블 머신을 사용하기는 어려워 보임.

- 다음 주는 추가 자료 조사를 쭉 진행하고, 웹과 서버를 연동하는 방법과 더불어 웹 개발 플랫폼에 웹과 DB를 업로드할 수 있는지 조사할 예정임.

<br/>

---
### 2022-02-05
#### 코드는 수정하고 6일 오전 중에 업로드 예정
1. 클라우드 서버에 웹 업로드
2. 웹 페이지 코드에 php 코드 삽입 중...
3. DB 테이블 수정함. (아직 생년월일 추가 방법은 찾지 못 함.)
4. DB 연결 방법은 아직 찾지 못 함.
5. 추가 자료 조사는 따로 카페에 업로드 예정

### EU 홈페이지: https://eutime.netlify.app/

<br/>

---
### 2022-02-06
하드웨어(아두이노 코드 Posture correction(ver.3))
- 아두이노 코드에 wifi접속코드 추가
- 센서 값을 DB에 보낼 php코드 작성
- 센서 값 저장할 DB생성(했지만 압축파일에 넣지 못했읍니당,, 다시 넣어 놓겠습니당)
<br/>
- wifi모듈(ESP-01)의 통신속도가 115200 bps로 초기 설정되어 있기 때문에 통신 속도를 9600으로 바꿔주는 작업이 필요 </br>
  1. 링크 참조: https://m.blog.naver.com/eduino/221152914869 
  2. 위에 링크에서 다운 받아지지 않는 파일은 Posture correction(ver.3)압축파일에 포함되어있음.
