//mudar os pinos todos de acordo com o caderno


#include <SoftwareSerial.h>
#include <SD.h>
#include <Servo.h>
#include <virtuabotixRTC.h>
#include <TimerOne.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define PGMSTR(x) (__FlashStringHelper*)(x)
#define SERVOUP_PIN 9
#define SERVODOWN_PIN 8

SoftwareSerial esp8266 (2, 3); //ESP8266 TX connected to Arduino Pin 2, ESP8266 RX connected to Arduino Pin 3
virtuabotixRTC relogio(5, 6, 7);
Servo servoUp;
Servo servoDown;

File file;

String ssid = "NOS-8290";
String password = "familia_onion";
String server = "kristaapi.herokuapp.com";

const char request[] PROGMEM  = {"POST /arduino/info HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};  //length 139
const char request1[] PROGMEM  = {"POST /arduino/a_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};  //length 138
const char request2[] PROGMEM  = {"POST /arduino/a_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request3[] PROGMEM  = {"POST /arduino/a_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request4[] PROGMEM  = {"POST /arduino/a_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request5[] PROGMEM  = {"POST /arduino/a_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request6[] PROGMEM  = {"POST /arduino/a_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request7[] PROGMEM  = {"POST /arduino/a_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request8[] PROGMEM  = {"POST /arduino/b_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request9[] PROGMEM  = {"POST /arduino/b_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request10[] PROGMEM  = {"POST /arduino/b_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request11[] PROGMEM  = {"POST /arduino/b_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request12[] PROGMEM  = {"POST /arduino/b_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request13[] PROGMEM  = {"POST /arduino/b_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request14[] PROGMEM  = {"POST /arduino/b_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request15[] PROGMEM  = {"POST /arduino/c_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request16[] PROGMEM  = {"POST /arduino/c_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request17[] PROGMEM  = {"POST /arduino/c_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request18[] PROGMEM  = {"POST /arduino/c_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request19[] PROGMEM  = {"POST /arduino/c_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request20[] PROGMEM  = {"POST /arduino/c_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request21[] PROGMEM  = {"POST /arduino/c_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request22[] PROGMEM  = {"POST /arduino/d_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request23[] PROGMEM  = {"POST /arduino/d_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request24[] PROGMEM  = {"POST /arduino/d_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request25[] PROGMEM  = {"POST /arduino/d_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request26[] PROGMEM  = {"POST /arduino/d_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request27[] PROGMEM  = {"POST /arduino/d_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char request28[] PROGMEM  = {"POST /arduino/d_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

PROGMEM const char * const links[]={
  request1, request2, request3, request4, request5, request6, request7, request8, request9, request10, request11, request12, request13, request14,
  request15, request16, request17, request18, request19, request20, request21, request22, request23, request24, request25, request26, request27, request28
};

int timeout = 2000;

void setup() {
  while(!SD.begin(10)){delay(100);}
  esp8266.begin(9600); // Should match ESP's current baudrate
  Serial.begin(9600);
  servoUp.attach(SERVOUP_PIN);
  servoDown.attach(SERVODOWN_PIN);

  servoUp.write(70);
  servoDown.write(80);
  delay(800);
  servoUp.detach();
  servoDown.detach();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Good morning");
  lcd.setCursor(2,1);
  lcd.print("How are you?");
}

void loop() {
  relogio.updateTime();
  String CLhour="";
  if(relogio.hours<10){
    CLhour+='0';
  }
  CLhour+=(String)relogio.hours;
  CLhour+='h';
  if(relogio.minutes<10){
    CLhour+='0';
  }
  CLhour+=relogio.minutes;

  if(CLhour=="00h01") espLink(); 

  servoUp.attach(SERVOUP_PIN);
  servoDown.attach(SERVODOWN_PIN);
  cardRead(CLhour);
  servoUp.detach();
  servoDown.detach();
}

void cardRead(String CLhour) {
  char text[100], *token=NULL, *SDhour=NULL;
  String meds;
  int counter=0;
  boolean save=false; 
  
  file=SD.open("horario.txt", FILE_READ);
  while (file.available()) {
    char c = file.read();
    if(c=='>') save=true;
    if(save){
      text[counter]=c;
      counter++;
    }
    if(c=='\n'){
      save=false;

      //falta ir buscar os medicamentos

      meds = text;
      meds.remove(0,7);
      
      token = strtok(text, ">");      
      SDhour = strtok(token,"&");

      if((String)SDhour==CLhour){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(meds);
        servoUp.write(100);
      }
      
      memset(text, 0, sizeof text);
      counter=0;
    }    
  }
  file.close();
  delay(60000);
  servoUp.write(70);
  servoDown.write(70);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Good morning");
  lcd.setCursor(2,1);
  lcd.print("How are you?");
}

void cardSave(){
  SD.remove("horario.txt");
  file = SD.open("horario.txt", FILE_WRITE);
  delay(100);
}

void espLink(){
  cardSave();
  setupESP8266();
  connectToWiFi();
  sendPOSTRequest();
}

void atCommand(String command, int timeout) {
  esp8266.println(command);
  long int time = millis();

  while( (time+timeout) > millis() ) {
    while(esp8266.available()) {
      char c = esp8266.read();
    }
  }
}

void setupESP8266() {
  atCommand("AT+RST", timeout);
  atCommand("AT+CWMODE=1", timeout);
}

void connectToWiFi() {
  atCommand("AT+CWJAP=\"" +ssid+"\",\"" + password + "\"", 6000);
  atCommand("AT+CIFSR", timeout);
}

void startTCPConnection() {
  esp8266.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");
  long int time = millis();

  while( (time+timeout) > millis() ) {
    while(esp8266.available()) {
      char c = esp8266.read();
    }
  }
}

void post(String line){
  String resposta = "";
  esp8266.println(line);
  boolean save = false;

  long int time = millis();

  while( (time+6000) > millis() ) {
    while(esp8266.available()) {
      char c = esp8266.read();
      if(c=='>'){
        save=true;
      }
      if(save) resposta+=c;
    }
  }
  Serial.println(resposta);
  if(file){
    file.println(resposta);
  }
}

void closeTCPConnection() {
  atCommand("AT+CIPCLOSE", timeout);
}

void sendPOSTRequest() {
  startTCPConnection();
  atCommand("AT+CIPSEND=139", timeout);
  post(PGMSTR(request));
  closeTCPConnection();

  for(int i=0;i<28;i++){
    startTCPConnection();
    atCommand("AT+CIPSEND=138", timeout);
    post(PGMSTR((char*)pgm_read_word(&(links[i]))));
    closeTCPConnection();
  }
  
  file.close();
}
