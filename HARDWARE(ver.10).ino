#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#include "OneM2MClient.h"
#include "m0_ota.h"

String ssid = "U+Net2429"; //자신의 wifi ssid입력
String PASSWORD = "1C5C021650"; //wifi 비밀번호
String host = "192.168.219.107"; // IP


int En0 = 9;  //  방석센서 쉴드
int En1 = 8;  //  방석센서 쉴드
int S0  = 7;
int S1  = 6;
int S2  = 5;
int S3  = 4;
int SIG_pin = A3;

//진동 센서(2개 x, y)
int x = 10; 
int y = 12;

SoftwareSerial mySerial(2,3); //RX,TX 

int sensor1;
int sensor2;
int sensor3;
int sensor4;
int sensor5;
int sensor6;
int sensor7;
int sensor8;
int sensor9;
int sensor10;
int sensor11;
int sensor12;
int sensor13;
int sensor14;
int sensor15;
int sensor16;
int sensor17;
int sensor18;
int sensor19;
int sensor20;
int sensor21;
int sensor22;
int sensor23;
int sensor24;
int sensor25;
int sensor26;
int sensor27;
int sensor28;
int sensor29;
int sensor30;
int sensor31;


unsigned long mqtt_previousMillis = 0;
unsigned long mqtt_interval = 8; // count
const unsigned long mqtt_base_led_interval = 250; // ms
unsigned long mqtt_led_interval = mqtt_base_led_interval; // ms
uint16_t mqtt_wait_count = 0;
unsigned long mqtt_watchdog_count = 0;

// for MQTT
#define _MQTT_INIT 1
#define _MQTT_CONNECT 2
#define _MQTT_CONNECTED 3
#define _MQTT_RECONNECT 4
#define _MQTT_READY 5
#define _MQTT_IDLE 6

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

char mqtt_id[16];
uint8_t MQTT_State = _MQTT_INIT;

char in_message[MQTT_MAX_PACKET_SIZE];
StaticJsonBuffer<MQTT_MAX_PACKET_SIZE> jsonBuffer;

unsigned long req_previousMillis = 0;
const long req_interval = 15000; // ms

unsigned long chk_previousMillis = 0;
const long chk_interval = 100; // ms
unsigned long chk_count = 0;

#define UPLOAD_UPLOADING 2
#define UPLOAD_UPLOADED 3
unsigned long uploading_previousMillis = 0;
const long uploading_interval = 10000; // ms
uint8_t UPLOAD_State = UPLOAD_UPLOADING;
uint8_t upload_retry_count = 0;

#define NCUBE_REQUESTED 1
#define NCUBE_REQUESTING 2

char req_id[10];
String state = "create_ae";
uint8_t nCube_State = NCUBE_REQUESTED;
uint8_t sequence = 0;

String strRef[8];
int strRef_length = 0;

#define QUEUE_SIZE 8
typedef struct _queue_t {
    uint8_t pop_idx;
    uint8_t push_idx;
    String ref[QUEUE_SIZE];
    String con[QUEUE_SIZE];
    String rqi[QUEUE_SIZE];
    unsigned long* previousMillis[QUEUE_SIZE];
} queue_t;

queue_t noti_q;
queue_t upload_q;

String body_str = "";

char resp_topic[48];
char noti_topic[48];

unsigned long system_watchdog = 0;

// -----------------------------------------------------------------------------
// User Define
// Period of Sensor Data, can make more
const unsigned long base_generate_interval = 20 * 1000;

// Information of CSE as Mobius with MQTT
const String FIRMWARE_VERSION = "1.0.0.0";
String AE_NAME = "EU";  //AE NAME 설정 부분
String AE_ID = "S" + AE_NAME;
const String CSE_ID = "/Mobius2";
const String CB_NAME = "Mobius";
const char* MOBIUS_MQTT_BROKER_IP = "203.253.128.161"; //"192.168.33.86";
const uint16_t MOBIUS_MQTT_BROKER_PORT = 1883;

OneM2MClient nCube;

// build tree of resource of oneM2M
void buildResource() {
    nCube.configResource(2, "/"+CB_NAME, AE_NAME);                       // AE resource

    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor1");          // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor2");          // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor3");          // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor4");          // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor5");          // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor6");          // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor7");          // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor8");          // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor9");          // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor10");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor11");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor12");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor13");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor14");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor15");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor16");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor17");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor18");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor19");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor20");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor21");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor22");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor23");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor24");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor25");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor26");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor27");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor28");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor29");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor30");         // Container resource
    nCube.configResource(3, "/"+CB_NAME+"/"+AE_NAME, "sensor31");         // Container resource

    nCube.configResource(23, "/"+CB_NAME+"/"+AE_NAME+"/update", "sub");  // Subscription resource
    nCube.configResource(23, "/"+CB_NAME+"/"+AE_NAME+"/led", "sub");     // Subscription resource
}

// void tvocGenProcess() {
//     unsigned long currentMillis = millis();
//     if (currentMillis - tvoc_generate_previousMillis >= tvoc_generate_interval) {
//         tvoc_generate_previousMillis = currentMillis;
//         tvoc_generate_interval = base_generate_interval + (random(1000));
//         if (state == "create_cin") {
//             String cnt = "tvoc";
//             String con = "\"?\"";

//             if(TasCCSSensor.available()) {
//                 if(!TasCCSSensor.readData()) {
//                     con = String(TasCCSSensor.getTVOC()/10);
//                     con = "\"" + con + "\"";

//                     char rqi[10];
//                     rand_str(rqi, 8);
//                     upload_q.ref[upload_q.push_idx] = "/"+CB_NAME+"/"+AE_NAME+"/"+cnt;
//                     upload_q.con[upload_q.push_idx] = con;
//                     upload_q.rqi[upload_q.push_idx] = String(rqi);
//                     upload_q.push_idx++;
//                     if(upload_q.push_idx >= QUEUE_SIZE) {
//                         upload_q.push_idx = 0;
//                     }
//                     if(upload_q.push_idx == upload_q.pop_idx) {
//                         upload_q.pop_idx++;
//                         if(upload_q.pop_idx >= QUEUE_SIZE) {
//                             upload_q.pop_idx = 0;
//                         }
//                     }

//                     Serial.println("pop : " + String(upload_q.pop_idx));
//                     Serial.println("push : " + String(upload_q.push_idx));
//                 }
//                 else {
//                     Serial.println("CCS811 tvoc ERROR!");
//                 }
//             }
//         }
//     }
// }
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
 
  int val = analogRead(SIG_pin); //SIG_pin의 value값 불러오기
 
  return val;
}

void connectWifi(){ 
  String join ="AT+CWJAP=\""+ssid+"\",\""+PASSWORD+"\""; 
  
  Serial.println("Connect Wifi..."); 
  mySerial.println(join); delay(10000); 
  if(mySerial.find("OK")) { 
    Serial.print("WIFI connect\n"); 
  }
  else{ 
    Serial.println("connect timeout\n"); 
  } 
  delay(1000); 
}

void httpclient(String char_input){
  delay(100); 
  Serial.println("connect TCP..."); 
  mySerial.println("AT+CIPSTART=\"TCP\",\""+host+"\",8787"); //8787부분은 포트번호 입력
  delay(500); if(Serial.find("ERROR")) 
  return; 
  
  Serial.println("Send data..."); 
  String url=char_input; 
  String cmd="GET /TEU.php?sensor1="+url+" HTTP/1.0\r\n\r\n"; 
  mySerial.print("AT+CIPSEND=");
  mySerial.println(cmd.length()); 
  Serial.print("AT+CIPSEND="); 
  Serial.println(cmd.length());
  if(mySerial.find(">")) { 
    Serial.print(">"); 
    }
    else { 
      mySerial.println("AT+CIPCLOSE"); 
      Serial.println("connect timeout"); 
      delay(1000); 
      return; 
      } 
      delay(500);
      
      mySerial.println(cmd);
      Serial.println(cmd); 
      delay(100);
      if(Serial.find("ERROR")) 
      return;
      mySerial.println("AT+CIPCLOSE");
      delay(100); 
      }

void setup() {
    // configure the LED pin for output mode
    // pinMode(ledPin, OUTPUT);

    // //Initialize serial:
    // Serial.begin(9600);
    // //while(!Serial);

    // noti_q.pop_idx = 0;
    // noti_q.push_idx = 0;
    // upload_q.pop_idx = 0;
    // upload_q.push_idx = 0;

    // WiFi_init();

    // delay(1000);
    Serial.begin(9600);
    mySerial.begin(9600);
  
    pinMode(En0, OUTPUT);
    pinMode(En1, OUTPUT);
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    pinMode(x, OUTPUT);
    pinMode(y, OUTPUT);

    connectWifi();
    delay(500); 

    byte mac[6];
    WiFi.macAddress(mac);
    sprintf(mqtt_id, "nCube-%.2X%.2X", mac[1], mac[0]);
    unsigned long seed = mac[0] + mac[1];
    randomSeed(seed);

    delay(500);


    String topic = "/oneM2M/resp/" + AE_ID + CSE_ID + "/json";
    topic.toCharArray(resp_topic, 64);

	topic = "/oneM2M/req" + CSE_ID + "/" + AE_ID + "/json";
    topic.toCharArray(noti_topic, 64);

    nCube.Init(CSE_ID, MOBIUS_MQTT_BROKER_IP, AE_ID);
    mqtt.setServer(MOBIUS_MQTT_BROKER_IP, MOBIUS_MQTT_BROKER_PORT);
    mqtt.setCallback(mqtt_message_handler);
    MQTT_State = _MQTT_INIT;

    buildResource();
    rand_str(req_id, 8);
    nCube_State = NCUBE_REQUESTED;

    //init OTA client
    OTAClient.begin(AE_NAME, FIRMWARE_VERSION);
}

int adc_read = 0;
int adc_data[32];

void loop() {
  sensor1 = readMux(0);
  sensor2 = readMux(1);
  sensor3 = readMux(2);
  sensor4 = readMux(3);
  sensor5 = readMux(4);
  sensor6 = readMux(5);
  sensor7 = readMux(6);
  sensor8 = readMux(7);
  sensor9 = readMux(8);
  sensor10 = readMux(9);
  sensor11 = readMux(10);
  sensor12 = readMux(11);
  sensor13 = readMux(12);
  sensor14 = readMux(13);
  sensor15 = readMux(14);
  sensor16 = readMux(15);
  sensor17 = readMux(16);
  sensor18 = readMux(17);
  sensor19 = readMux(18);
  sensor20 = readMux(19);
  sensor21 = readMux(20);
  sensor22 = readMux(21);
  sensor23 = readMux(22);
  sensor24 = readMux(23);
  sensor25 = readMux(24);
  sensor26 = readMux(25);
  sensor27 = readMux(26);
  sensor28 = readMux(27);
  sensor29 = readMux(28);
  sensor30 = readMux(29);
  sensor31 = readMux(30);
    // nCube loop
    nCube_loop();

    // user defined loop
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

 String str_output = String(sensor1)+"&sensor2="+String(sensor2)+"&sensor3="+String(sensor3)+"&sensor4="+String(sensor4)+"&sensor5="+String(sensor5)+"&sensor6="+String(sensor6)+"&sensor7="+String(sensor7)+"&sensor8="+String(sensor8)+"&sensor9="+String(sensor9)+"&sensor10="+String(sensor10)+
                     "&sensor11="+String(sensor11)+"&sensor12="+String(sensor12)+"&sensor13="+String(sensor13)+"&sensor14="+String(sensor14)+"&sensor15="+String(sensor15)+"&sensor16="+String(sensor16)+"&sensor17="+String(sensor17)+"&sensor18="+String(sensor18)+"&sensor19="+String(sensor19)+"&sensor20="+String(sensor20)+
                     "&sensor21="+String(sensor21)+"&sensor22="+String(sensor22)+"&sensor23="+String(sensor23)+"&sensor24="+String(sensor24)+"&sensor25="+String(sensor25)+"&sensor26="+String(sensor26)+"&sensor27="+String(sensor27)+"&sensor28="+String(sensor28)+"&sensor29="+String(sensor29)+"&sensor30="+String(sensor30)+"&sensor31="+String(sensor31); 
 delay(1000); 
 httpclient(str_output); 
 delay(1000);

//Serial.find("+IPD"); 
while (mySerial.available()) 
{ 
  char response = mySerial.read();
  Serial.write(response);
  if(response=='\r') Serial.print('\n'); 
  }
  Serial.println("\n==================================\n"); 
  delay(2000);

  //delay(3000);//loop() 딜레이 3초 
}


//------------------------------------------------------------------------------
// nCube core functions
//------------------------------------------------------------------------------

void nCube_loop() {
    WiFi_chkconnect();
    if (!mqtt.loop()) {
        MQTT_State = _MQTT_CONNECT;
        //digitalWrite(13, HIGH);
        mqtt_reconnect();
        //digitalWrite(13, LOW);
    }
    else {
        MQTT_State = _MQTT_CONNECTED;
    }

    chkState();
    publisher();
    otaProcess();
    uploadProcess();
}

void rand_str(char *dest, size_t length) {
    char charset[] = "0123456789"
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        //size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        //*dest++ = charset[index];

        size_t index = random(62);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

void WiFi_init() {
    if(USE_WIFI) {
        // begin WiFi
        digitalWrite(ledPin, HIGH);
        WiFi.setPins(WINC_CS, WINC_IRQ, WINC_RST, WINC_EN);
        if (WiFi.status() == WL_NO_SHIELD) { // check for the presence of the shield:
            Serial.println("WiFi shield not present");
            // don't continue:
            while (true) {
                digitalWrite(ledPin, HIGH);
                delay(100);
                digitalWrite(ledPin, LOW);
                delay(100);
            }
        }
        digitalWrite(ledPin, LOW);
    }

    WIFI_State = WIFI_INIT;
}

void WiFi_chkconnect() {
    if(USE_WIFI) {
        if(WIFI_State == WIFI_INIT) {
            digitalWrite(ledPin, HIGH);

            Serial.println("beginProvision - WIFI_INIT");
            WiFi.beginProvision();
//            WiFi.begin("FILab", "badacafe00");

            WIFI_State = WIFI_CONNECT;
            wifi_previousMillis = 0;
            wifi_wait_count = 0;
            noti_q.pop_idx = 0;
            noti_q.push_idx = 0;
            upload_q.pop_idx = 0;
            upload_q.push_idx = 0;
        }
        else if(WIFI_State == WIFI_CONNECTED) {
            if (WiFi.status() == WL_CONNECTED) {
                return;
            }

            wifi_wait_count = 0;
            if(WIFI_State == WIFI_CONNECTED) {
                WIFI_State = WIFI_RECONNECT;
                wifi_previousMillis = 0;
                wifi_wait_count = 0;
                noti_q.pop_idx = 0;
                noti_q.push_idx = 0;
                upload_q.pop_idx = 0;
                upload_q.push_idx = 0;
            }
            else {
                WIFI_State = WIFI_CONNECT;
                wifi_previousMillis = 0;
                wifi_wait_count = 0;
                noti_q.pop_idx = 0;
                noti_q.push_idx = 0;
                upload_q.pop_idx = 0;
                upload_q.push_idx = 0;
            }
            //nCube.MQTT_init(AE_ID);
        }
        else if(WIFI_State == WIFI_CONNECT) {
            unsigned long currentMillis = millis();
            if (currentMillis - wifi_previousMillis >= wifi_led_interval) {
                wifi_previousMillis = currentMillis;
                if(wifi_wait_count++ >= wifi_interval) {
                    wifi_wait_count = 0;
                    if (WiFi.status() != WL_CONNECTED) {
                        Serial.println("Provisioning......");
                    }
                }
                else {
                    if(wifi_wait_count % 2) {
                        digitalWrite(ledPin, HIGH);
                    }
                    else {
                        digitalWrite(ledPin, LOW);
                    }
                }
            }
            else {
                if (WiFi.status() == WL_CONNECTED) {
                    // you're connected now, so print out the status:
                    printWiFiStatus();

                    digitalWrite(ledPin, LOW);

                    WIFI_State = WIFI_CONNECTED;
                    wifi_previousMillis = 0;
                    wifi_wait_count = 0;
                    noti_q.pop_idx = 0;
                    noti_q.push_idx = 0;
                    upload_q.pop_idx = 0;
                    upload_q.push_idx = 0;
                }
            }
        }
        else if(WIFI_State == WIFI_RECONNECT) {
            digitalWrite(ledPin, HIGH);

            unsigned long currentMillis = millis();
            if (currentMillis - wifi_previousMillis >= wifi_led_interval) {
                wifi_previousMillis = currentMillis;
                if(wifi_wait_count++ >= wifi_interval) {
                    wifi_wait_count = 0;
                    if (WiFi.status() != WL_CONNECTED) {
                        Serial.print("Attempting to connect to SSID: ");
                        Serial.println("previous SSID");

                        WiFi.begin();
                    }
                }
                else {
                    if(wifi_wait_count % 2) {
                        digitalWrite(ledPin, HIGH);
                    }
                    else {
                        digitalWrite(ledPin, LOW);
                    }
                }
            }
            else {
                if (WiFi.status() == WL_CONNECTED) {
                    Serial.println("Connected to wifi");
                    printWiFiStatus();

                    digitalWrite(ledPin, LOW);

                    WIFI_State = WIFI_CONNECTED;
                    wifi_previousMillis = 0;
                    wifi_wait_count = 0;
                }
            }
        }
    }
}

void printWiFiStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

void otaProcess() {
    if(WIFI_State == WIFI_CONNECTED && MQTT_State == _MQTT_CONNECTED) {
        if (OTAClient.finished()) {
        }
        else {
            OTAClient.poll();
        }
    }
}

void publisher() {
    unsigned long currentMillis = millis();
    if (currentMillis - req_previousMillis >= req_interval) {
        req_previousMillis = currentMillis;

        rand_str(req_id, 8);
        nCube_State = NCUBE_REQUESTED;
    }

    if(nCube_State == NCUBE_REQUESTED && WIFI_State == WIFI_CONNECTED && MQTT_State == _MQTT_CONNECTED) {
        if (state == "create_ae") {
            Serial.print(state + " - ");
            Serial.print(String(sequence));
            Serial.print(" - ");
            Serial.println(String(req_id));
            nCube_State = NCUBE_REQUESTING;
            body_str = nCube.createAE(mqtt, req_id, 0, "3.14");

            if (body_str == "0") {
        		Serial.println(F("REQUEST Failed"));
        	}
        	else {
        		Serial.print("Request [");
        		Serial.print(nCube.getReqTopic());
        		Serial.print("] ----> ");
        		Serial.println(body_str.length()+1);
        		Serial.println(body_str);
        	}
            //digitalWrite(ledPin, HIGH);
        }
        else if (state == "create_cnt") {
            Serial.print(state + " - ");
            Serial.print(String(sequence));
            Serial.print(" - ");
            Serial.println(String(req_id));
            nCube_State = NCUBE_REQUESTING;
            body_str = nCube.createCnt(mqtt, req_id, sequence);
            if (body_str == "0") {
        		Serial.println(F("REQUEST Failed"));
        	}
        	else {
        		Serial.print("Request [");
        		Serial.print(nCube.getReqTopic());
        		Serial.print("] ----> ");
        		Serial.println(body_str.length()+1);
        		Serial.println(body_str);
        	}
            //digitalWrite(ledPin, HIGH);
        }
        else if (state == "delete_sub") {
            Serial.print(state + " - ");
            Serial.print(String(sequence));
            Serial.print(" - ");
            Serial.println(String(req_id));
            nCube_State = NCUBE_REQUESTING;
            body_str = nCube.deleteSub(mqtt, req_id, sequence);
            if (body_str == "0") {
        		Serial.println(F("REQUEST Failed"));
        	}
        	else {
        		Serial.print("Request [");
        		Serial.print(nCube.getReqTopic());
        		Serial.print("] ----> ");
        		Serial.println(body_str.length()+1);
        		Serial.println(body_str);
        	}
            //digitalWrite(ledPin, HIGH);
        }
        else if (state == "create_sub") {
            Serial.print(state + " - ");
            Serial.print(String(sequence));
            Serial.print(" - ");
            Serial.println(String(req_id));
            nCube_State = NCUBE_REQUESTING;
            body_str = nCube.createSub(mqtt, req_id, sequence);
            if (body_str == "0") {
        		Serial.println(F("REQUEST Failed"));
        	}
        	else {
        		Serial.print("Request [");
        		Serial.print(nCube.getReqTopic());
        		Serial.print("] ----> ");
        		Serial.println(body_str.length()+1);
        		Serial.println(body_str);
        	}
            //digitalWrite(ledPin, HIGH);
        }
        else if (state == "create_cin") {
        }
    }
}

unsigned long mqtt_sequence = 0;
void chkState() {
    unsigned long currentMillis = millis();
    if (currentMillis - chk_previousMillis >= chk_interval) {
        chk_previousMillis = currentMillis;

        system_watchdog++;
        if(system_watchdog > 9000) {
            if(system_watchdog % 2) {
                digitalWrite(ledPin, HIGH);
            }
            else {
                digitalWrite(ledPin, LOW);
            }
        }
        else if(system_watchdog > 18000) {
            NVIC_SystemReset();
        }

        if(WIFI_State == WIFI_CONNECT) {
            Serial.println("WIFI_CONNECT");
            MQTT_State = _MQTT_INIT;
        }
        else if(WIFI_State == WIFI_RECONNECT) {
            Serial.println("WIFI_RECONNECT");
            MQTT_State = _MQTT_INIT;
        }
        else if(WIFI_State == WIFI_CONNECTED && MQTT_State == _MQTT_INIT) {
            MQTT_State = _MQTT_CONNECT;
        }

        if(MQTT_State == _MQTT_CONNECT) {
            Serial.println("_MQTT_CONNECT");
        }

        /*if(WIFI_State == WIFI_CONNECTED && MQTT_State == _MQTT_CONNECTED) {
            chk_count++;
            if(chk_count >= 100) {
                chk_count = 0;

                //noInterrupts();
                body_str = nCube.heartbeat(mqtt);
                // char seq[10];
                // sprintf(seq, "%ld", ++mqtt_sequence);
                // mqtt.publish("/nCube/count/test", seq, strlen(seq));
                // Serial.println(String(mqtt_sequence));
                //interrupts();

                if (body_str == "Failed") {
                    Serial.println(F("Heartbeat Failed"));
                }
                else {
                    Serial.print("Send heartbeat [");
                    Serial.print(nCube.getHeartbeatTopic());
                    Serial.print("] ----> ");
                    Serial.println(body_str.length()+1);
                    Serial.println(body_str);
                    system_watchdog = 0;
                }
            }
        }*/
    }
}

void Split(String sData, char cSeparator)
{
    int nCount = 0;
    int nGetIndex = 0 ;
    strRef_length = 0;

    String sTemp = "";
    String sCopy = sData;

    while(true) {
        nGetIndex = sCopy.indexOf(cSeparator);

        if(-1 != nGetIndex) {
            sTemp = sCopy.substring(0, nGetIndex);
            strRef[strRef_length++] = sTemp;
            sCopy = sCopy.substring(nGetIndex + 1);
        }
        else {
            strRef[strRef_length++] = sCopy;
            break;
        }
        ++nCount;
    }
}

void mqtt_reconnect() {
    if(WIFI_State == WIFI_CONNECTED && MQTT_State == _MQTT_CONNECT) {
        unsigned long currentMillis = millis();
        if (currentMillis - mqtt_previousMillis >= mqtt_led_interval) {
            mqtt_led_interval = mqtt_base_led_interval + random(mqtt_base_led_interval);
            mqtt_previousMillis = currentMillis;
            if(mqtt_wait_count++ >= (mqtt_interval)) {
                mqtt_wait_count = 0;

                Serial.print("Attempting MQTT connection...");
                // Attempt to connect
                //rand_str(mqtt_id, 8);
                if (mqtt.connect(mqtt_id)) {
                    mqtt_watchdog_count = 0;
                    Serial.println("connected");

                    if (mqtt.subscribe(resp_topic)) {
                        Serial.println(String(resp_topic) + " Successfully subscribed");
                    }

                    if (mqtt.subscribe(noti_topic)) {
                        Serial.println(String(noti_topic) + " Successfully subscribed");
                    }

                    MQTT_State = _MQTT_CONNECTED;
                    nCube.reset_heartbeat();
                }
                else {
                    Serial.print("failed, rc=");
                    Serial.print(mqtt.state());
                    Serial.println(" try again in 2 seconds");
                    mqtt_watchdog_count++;
                    if(mqtt_watchdog_count > 10) {
                        NVIC_SystemReset();
                    }
                }
            }
            else {
                if(mqtt_wait_count % 2) {
                    digitalWrite(ledPin, HIGH);
                }
                else {
                    digitalWrite(ledPin, LOW);
                }
            }
        }
    }
}

void mqtt_message_handler(char* topic_in, byte* payload, unsigned int length) {
    String topic = String(topic_in);

    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] <---- ");
    Serial.println(length);

    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    //noInterrupts();

    if (topic.substring(8,12) == "resp") {
        memset((char*)in_message, '\0', length+1);
        memcpy((char*)in_message, payload, length);
        JsonObject& resp_root = jsonBuffer.parseObject(in_message);

        if (!resp_root.success()) {
            Serial.println(F("parseObject() failed"));
            jsonBuffer.clear();
            return;
        }

        wifiClient.flush();

        resp_handler(resp_root["rsc"], resp_root["rqi"]);

        jsonBuffer.clear();
    }
    else if(topic.substring(8,11) == "req") {
        memset((char*)in_message, '\0', length+1);
        memcpy((char*)in_message, payload, length);
        JsonObject& req_root = jsonBuffer.parseObject(in_message);

        if (!req_root.success()) {
            Serial.println(F("parseObject() failed"));
            return;
        }

        wifiClient.flush();

        noti_handler(req_root["pc"]["m2m:sgn"]["sur"], req_root["rqi"], req_root["pc"]["m2m:sgn"]["nev"]["rep"]["m2m:cin"]["con"]);

        jsonBuffer.clear();
    }
    //interrupts();
    system_watchdog = 0;
}

void noti_handler(String sur, String rqi, String con) {
    if (state == "create_cin") {
        Serial.print("<---- ");
        if(sur.charAt(0) != '/') {
            sur = '/' + sur;
            Serial.println(sur);
        }
        else {
            Serial.println(sur);
        }

        String valid_sur = nCube.validSur(sur);
        if (valid_sur != "empty") {
            noti_q.ref[noti_q.push_idx] = valid_sur;
            noti_q.con[noti_q.push_idx] = con;
            noti_q.rqi[noti_q.push_idx] = rqi;
            noti_q.push_idx++;
            if(noti_q.push_idx >= QUEUE_SIZE) {
                noti_q.push_idx = 0;
            }
            if(noti_q.push_idx == noti_q.pop_idx) {
                noti_q.pop_idx++;
                if(noti_q.pop_idx >= QUEUE_SIZE) {
                    noti_q.pop_idx = 0;
                }
            }
        }
    }
}

void resp_handler(int response_code, String response_id) {
    String request_id = String(req_id);

    if (request_id == response_id) {
        if (response_code == 2000 || response_code == 2001 || response_code == 2002 || response_code == 4105 || response_code == 4004) {
            Serial.print("<---- ");
            Serial.println(response_code);
            if (state == "create_ae") {
                sequence++;
                if(sequence >= nCube.getAeCount()) {
                    state = "create_cnt";
                    sequence = 0;
                }
                rand_str(req_id, 8);
                nCube_State = NCUBE_REQUESTED;
            }
            else if (state == "create_cnt") {
                sequence++;
                if(sequence >= nCube.getCntCount()) {
                    state = "delete_sub";
                    sequence = 0;
                }
                rand_str(req_id, 8);
                nCube_State = NCUBE_REQUESTED;
            }
            else if(state == "delete_sub") {
                sequence++;
                if(sequence >= nCube.getSubCount()) {
                    state = "create_sub";
                    sequence = 0;
                }
                rand_str(req_id, 8);
                nCube_State = NCUBE_REQUESTED;
            }
            else if (state == "create_sub") {
                sequence++;
                if(sequence >= nCube.getSubCount()) {
                    state = "create_cin";
                    sequence = 0;
                }
                rand_str(req_id, 8);
                nCube_State = NCUBE_REQUESTED;
            }
            else if (state == "create_cin") {
                upload_retry_count = 0;
                if(upload_q.pop_idx == upload_q.push_idx) {

                }
                else {
                    *upload_q.previousMillis[upload_q.pop_idx] = millis();

                    upload_q.pop_idx++;
                    if(upload_q.pop_idx >= QUEUE_SIZE) {
                        upload_q.pop_idx = 0;
                    }
                }
            }
            //digitalWrite(ledPin, LOW);
            UPLOAD_State = UPLOAD_UPLOADED;
        }
    }
}

void uploadProcess() {
    if(WIFI_State == WIFI_CONNECTED && MQTT_State == _MQTT_CONNECTED) {
        unsigned long currentMillis = millis();
        if (currentMillis - uploading_previousMillis >= uploading_interval) {
            uploading_previousMillis = currentMillis;

            if (state == "create_cin") {
                if(UPLOAD_State == UPLOAD_UPLOADING) {
                    Serial.println("upload timeout");
                }

                UPLOAD_State = UPLOAD_UPLOADED;
                upload_retry_count++;
                if(upload_retry_count > 2) {
                    upload_retry_count = 0;
                    if(upload_q.pop_idx == upload_q.push_idx) {

                    }
                    else {
                        upload_q.pop_idx++;
                        if(upload_q.pop_idx >= QUEUE_SIZE) {
                            upload_q.pop_idx = 0;
                        }
                    }
                }
            }
        }

        if((UPLOAD_State == UPLOAD_UPLOADED) && (upload_q.pop_idx != upload_q.push_idx)) {
            if (wifiClient.available()) {
                return;
            }

            uploading_previousMillis = millis();
            UPLOAD_State = UPLOAD_UPLOADING;

            upload_q.rqi[upload_q.pop_idx].toCharArray(req_id, 10);

            Serial.println("pop : " + String(upload_q.pop_idx));
            Serial.println("push : " + String(upload_q.push_idx));
            //noInterrupts();
            body_str = nCube.createCin(mqtt, upload_q.rqi[upload_q.pop_idx], upload_q.ref[upload_q.pop_idx], upload_q.con[upload_q.pop_idx]);
            wifiClient.flush();
            //interrupts();
            if (body_str == "0") {
        		Serial.println(F("REQUEST Failed"));
        	}
        	else {
                system_watchdog = 0;
        		Serial.print("Request [");
        		Serial.print(nCube.getReqTopic());
        		Serial.print("] ----> ");
        		Serial.println(body_str.length()+1);
        		Serial.println(body_str);
        	}
        }
    }
}
