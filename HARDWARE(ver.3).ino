//방석센서 쉴드 내부에 74HC4067(멀티플렉서) 2개가 내장되어있기 때문에 GPIO 6개로 32개 센서 연결 가능  
//방석센서(En0, En1, S0, S1, S2, S3)
int En0 = 7;  
int En1 = 6;  
int S0  = 5;
int S1  = 4;
int S2  = 3;
int S3  = 2;
 
int SIG_pin = A3;

//진동 센서(2개 x, y)
int x = 9; 
int y = 10; 

 
void setup() {
  Serial.begin(9600);
  pinMode(En0, OUTPUT);
  pinMode(En1, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(x, OUTPUT);
  pinMode(y, OUTPUT);
}

int adc_read = 0;
int adc_data[32];

void loop() { 
  int left = readMux(0)+ readMux(1)+ readMux(5)+ readMux(6)+ readMux(7)+ readMux(8) + readMux(10); //왼쪽으로 쏠렸을 때 
  int right = readMux(20) + readMux(22) + readMux(23) + readMux(24) + readMux(25)+ readMux(30); //오른쪽으로 쏠렸을 때 
  //방석센서의 값 시리어 모니터에 출력(마지막 32번째 값은 더미값)
  for(int i = 0; i < 32; i++){ 
    adc_read = 0;
    adc_read = readMux(i);
    adc_data[32] = adc_read;

    Serial.print(adc_read); 
    Serial.print(",");   
  }
  // 시리얼 모니터에서 방석센서의 값 뒤에 left, right값 출력(값 확인용)
  Serial.print("  ");
  Serial.print(left); 
  Serial.print(",");
  Serial.print(right);
  Serial.println(" ");  //다음줄로 넘어감
  
  vibration(); //진동센서 함수 
 
  delay(3000);//loop() 딜레이 3초 
}


void vibration() {

   int left = readMux(0)+ readMux(1)+ readMux(5)+ readMux(6)+ readMux(7)+ readMux(8) + readMux(10); //왼쪽으로 쏠렸을 때
   int right = readMux(20) + readMux(22) + readMux(23) + readMux(24) + readMux(25)+ readMux(30); //오른쪽으로 쏠렸을 때

  //진동센서 작동하는 조건
   if(400 < left) {      //left의 값이 400보다 클 때
      analogWrite(x, 60);//왼쪽 모터 켜짐
   }
   else {                //left의 값이 400보다 작을 때
      analogWrite(x, 0);//왼쪽 모터 꺼짐
  }
   
  if(400 < right) {        //right의 값이 400보다 클 때
      analogWrite(y, 60); //오른쪽 모터 켜짐
   }
   else {                 //right의 값이 400보다 작을 때
      analogWrite(y, 0); //오른쪽 모터 꺼짐
   }
}

 
int readMux(int channel){
  int controlPin[] = {S0,S1,S2,S3,En0,En1};
 
  int muxChannel[32][6]={
    {0,0,0,0,0,1}, //channel 0
    {0,0,0,1,0,1}, //channel 1
    {0,0,1,0,0,1}, //channel 2
    {0,0,1,1,0,1}, //channel 3
    {0,1,0,0,0,1}, //channel 4
    {0,1,0,1,0,1}, //channel 5
    {0,1,1,0,0,1}, //channel 6
    {0,1,1,1,0,1}, //channel 7
    {1,0,0,0,0,1}, //channel 8
    {1,0,0,1,0,1}, //channel 9
    {1,0,1,0,0,1}, //channel 10
    {1,0,1,1,0,1}, //channel 11
    {1,1,0,0,0,1}, //channel 12
    {1,1,0,1,0,1}, //channel 13
    {1,1,1,0,0,1}, //channel 14
    {1,1,1,1,0,1}, //channel 15
    {0,0,0,0,1,0}, //channel 16
    {0,0,0,1,1,0}, //channel 17
    {0,0,1,0,1,0}, //channel 18
    {0,0,1,1,1,0}, //channel 19
    {0,1,0,0,1,0}, //channel 20
    {0,1,0,1,1,0}, //channel 21
    {0,1,1,0,1,0}, //channel 22
    {0,1,1,1,1,0}, //channel 23
    {1,0,0,0,1,0}, //channel 24
    {1,0,0,1,1,0}, //channel 25
    {1,0,1,0,1,0}, //channel 26
    {1,0,1,1,1,0}, //channel 27
    {1,1,0,0,1,0}, //channel 28
    {1,1,0,1,1,0}, //channel 29
    {1,1,1,0,1,0}, //channel 30
    {1,1,1,1,1,0}  //channel 31
  };
 
  //loop through the 6 sig
  for(int i = 0; i < 6; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
 
  int val = analogRead(SIG_pin); //아날로그값 읽어오기
 
  return val;
}
