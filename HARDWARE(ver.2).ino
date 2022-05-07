int En0 = 7;  //  Low enabled
int En1 = 6;  //  Low enabled

int S0  = 5;
int S1  = 4;
int S2  = 3;
int S3  = 2;
 
int SIG_pin = A3;

int x  = 9;
int y  = 10;
 
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
  for(int i = 0; i < 32; i ++){ 
    adc_read = 0;
    adc_read = readMux(i);
    adc_data[32] = adc_read;

    Serial.print(adc_read); 
    Serial.print(",");   
  }
  Serial.println(" ");  
  
  doSomething();
 
  delay(3000);
}

void doSomething() {
  int pressure_left = 0;
  int pressure_right = 0;
  
   pressure_left = adc_data[5] + adc_data[6] + adc_data[7] + adc_data[8] + adc_data[0] + adc_data[1] + adc_data[10];
   pressure_right = adc_data[25] + adc_data[24] + adc_data[23] + adc_data[22] + adc_data[30] + adc_data[29] + adc_data[20];

   // 400이 한계
   if(300 < pressure_left) {
       digitalWrite(x, HIGH); //왼쪽 진동센서 켜짐
   }
   else {
       digitalWrite(x, LOW); //왼쪽 진동센서 꺼짐
   }
   
   if(300 < pressure_right) {
       digitalWrite(y, HIGH); //오른쪽 진동센서 켜짐
   }
   else {
       digitalWrite(y, LOW); //오른쪽 진동센서 꺼짐
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
 
  //SIG핀의 값 val에 읽어오기
  int val = analogRead(SIG_pin);
 
  return val;
}
