/*
  PINOUT DOS COMPONENTES:

    I2C:
      - SCL => A5
      - SDA => A4

    RTC:
      - CLK => 4
      - DAT => 3
      - RST => 2

    ESP8266:
      - RX => 7
      - TX => 6

    SD:
      - SCK => 13
      - MISO => 12
      - MOSI => 11
      - CS => 10

    BUZZER:
      - SIGNAL => 5
*/


#include <SoftwareSerial.h>
#include <SD.h>
#include <Servo.h>
#include <virtuabotixRTC.h>
#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>

#define PGMSTR(x) (__FlashStringHelper*)(x)   //função auxiliar para ler a memória flash
#define SERVOUP_PIN 9
#define SERVODOWN_PIN 8
#define BUZZER 5

virtuabotixRTC relogio(2, 3, 4);  //declaração do relógio
LiquidCrystal_I2C lcd(0x27,16,2);  //declaração do LCD de 16x2
SoftwareSerial esp8266 (6, 7); //declaração do módulo de wifi
Servo servoUp;  //declaração do servo superior
Servo servoDown;  //declaração do servo inferior

File file;

//definições para ligação à internet
String ssid = "NOS-8290";
String password = "nnn";
String server = "kristaapi.herokuapp.com";

//LINKS PARA IR BUSCAR A INFO A BASE DE DADOS
const char info[] PROGMEM  = {"POST /arduino/info HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

const char dom_a[] PROGMEM = {"POST /arduino/a_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char dom_b[] PROGMEM = {"POST /arduino/b_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char dom_c[] PROGMEM = {"POST /arduino/c_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char dom_d[] PROGMEM = {"POST /arduino/d_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

const char seg_a[] PROGMEM = {"POST /arduino/a_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char seg_b[] PROGMEM = {"POST /arduino/b_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char seg_c[] PROGMEM = {"POST /arduino/c_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char seg_d[] PROGMEM = {"POST /arduino/d_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

const char ter_a[] PROGMEM = {"POST /arduino/a_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char ter_b[] PROGMEM = {"POST /arduino/b_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char ter_c[] PROGMEM = {"POST /arduino/c_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char ter_d[] PROGMEM = {"POST /arduino/d_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

const char qua_a[] PROGMEM = {"POST /arduino/a_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qua_b[] PROGMEM = {"POST /arduino/b_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qua_c[] PROGMEM = {"POST /arduino/c_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qua_d[] PROGMEM = {"POST /arduino/d_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

const char qui_a[] PROGMEM = {"POST /arduino/a_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qui_b[] PROGMEM = {"POST /arduino/b_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qui_c[] PROGMEM = {"POST /arduino/c_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qui_d[] PROGMEM = {"POST /arduino/d_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

const char sex_a[] PROGMEM = {"POST /arduino/a_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sex_b[] PROGMEM = {"POST /arduino/b_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sex_c[] PROGMEM = {"POST /arduino/c_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sex_d[] PROGMEM = {"POST /arduino/d_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

const char sab_a[] PROGMEM = {"POST /arduino/a_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sab_b[] PROGMEM = {"POST /arduino/b_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sab_c[] PROGMEM = {"POST /arduino/c_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sab_d[] PROGMEM = {"POST /arduino/d_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

PROGMEM const char * const links[] = {
  dom_a, dom_b, dom_c, dom_d, seg_a, seg_b, seg_c, seg_d, ter_a, ter_b, ter_c, ter_d, qua_a, qua_b, qua_c, qua_d, qui_a, qui_b, qui_c, qui_d, sex_a, sex_b, sex_c, sex_d, sab_a, sab_b, sab_c, sab_d 
};

const char dom[] PROGMEM = {"Dom - "};
const char seg[] PROGMEM = {"Seg - "};
const char ter[] PROGMEM = {"Ter - "};
const char qua[] PROGMEM = {"Qua - "};
const char qui[] PROGMEM = {"Qui - "};
const char sex[] PROGMEM = {"Sex - "};
const char sab[] PROGMEM = {"Sab - "};

PROGMEM const char * const diasDaSemana[] = {dom, seg, ter, qua, qui, sex, sab}; 


int timeout = 3000;

void setup() {
  while(!SD.begin(10)){delay(100);}
  esp8266.begin(9600);
  Serial.begin(9600);
  servoUp.attach(SERVOUP_PIN);
  servoDown.attach(SERVODOWN_PIN);
  pinMode(BUZZER, OUTPUT);
  servoUp.write(65);
  servoDown.write(100);
  
  lcdInit();
  
  delay(1000);
}

void loop() {
  String CLhour = hora();

  cardRead(CLhour, relogio.dayofweek);

  if(CLhour=="23h41") subs();

  if(CLhour=="00h57"){
    servoUp.detach();
    servoDown.detach();
    espLink();
    servoUp.attach(SERVOUP_PIN);
    servoDown.attach(SERVODOWN_PIN);
  }

}

void lcdWrite() {
  String CLhour = hora();

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(PGMSTR((char*)pgm_read_word(&(diasDaSemana[relogio.dayofweek - 1]))));
  lcd.print(CLhour); 
}

void lcdInit() {
  lcd.init();
  lcd.backlight();
  lcdWrite();
}

void tom(float frequencia){
  tone(BUZZER, frequencia);  
  delay(100);        
  noTone(BUZZER);    
  delay(100);        
}

void despertador(){
  tom(523.2511);
  tom(523.2511);
  tom(174.6141);
  tom(523.2511);
  tom(349.2282);
  tom(349.2282);
  delay(200);
  tom(349.2282);
  tom(391.9954);
  tom(391.9954);
  tom(130.8128);
  tom(391.9954);
  tom(261.6256);
  tom(261.6256);
  delay(200);
  tom(261.6256);
}

String hora() {
  relogio.updateTime();
  String hour="";
  if(relogio.hours<10){
    hour+='0';
  }
  hour+=(String)relogio.hours;
  hour+='h';
  if(relogio.minutes<10){
    hour+='0';
  }
  hour+=relogio.minutes;

  return hour;
}

void cardRead(String CLhour, int DayOfWeekCL) { 
  char text[50], SDhour[10], meds[43];
  int counter=0, lines=0, dayOfWeekSD=1; //domingo = 1; segunda = 2; ... ; sexta = 6; sábado = 7
  boolean save=false, skip=true; 
  
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
      int len = strlen(text)-2;

      for(int i=0;i<5;i++) SDhour[i] = text[i+1];
      for(int i=7;i<len;i++) meds[i-7] = text[i];

      if(!skip){lines++;}
      if(skip){skip=false;}     //permite saltar a primeira linha do ficheiro de texto

      if((String)SDhour==CLhour && DayOfWeekCL==dayOfWeekSD){                
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print(meds);
        
        switch(lines){        //define o servo e o angulo de abertura
          case 1:
            servoUp.write(120); 
            break;
          case 2:
            servoUp.write(10); 
            break;
          case 3:
            servoDown.write(155);
            break;
          case 4:
            servoDown.write(30); 
            break;
        }
        
        despertador();
        
        delay(60000);

        servoUp.write(65);
        servoDown.write(100);
      }

      if(lines==4){
        lines=0;
        dayOfWeekSD++;
      }
      
      for(int i = 0; i < sizeof(text);  ++i ) text[i] = (char)0;
      for(int i = 0; i < sizeof(SDhour);  ++i ) SDhour[i] = (char)0;
      for(int i = 0; i < sizeof(meds);  ++i ) meds[i] = (char)0;
      
      counter=0;
    }    
  }
  
  file.close();
           
  lcdWrite();
  
  delay(1000);
}

void subs() {
  servoUp.write(150);
  servoDown.write(5);
  delay(900000);
  servoUp.write(65);
  servoDown.write(100); 
}

void cardSave(){
  SD.remove("horario.txt");
  file = SD.open("horario.txt", FILE_WRITE);
  delay(100);
}

void check() {
  String file1, file2;
  boolean valid = true;
  file = SD.open("horario.txt",FILE_READ);
  if(file.read()!='>') valid=false;
  file.close();
  if(valid){
    file1="horario.txt";
    file2="backup.txt";
  }
  else{
    file1="backup.txt";
    file2="horario.txt";
  }
  char line[50];
  SD.remove(file2);
  for(int i=1;i<=29;i++){
    int linha=1;
    int counter=0;
    file = SD.open(file1, FILE_READ);
    while(file.available()){
      char c = file.read();
      if(linha==i){
        line[counter]=c;
        counter++;
      }
      if(c=='\n') linha++;
      if(linha>i)break;
    }
    file.close();
    file = SD.open(file2, FILE_WRITE);
    file.print(line);
    Serial.print(line);
    file.close();
    for(int i = 0; i < sizeof(line);  ++i ) line[i] = (char)0;
  }
}

void espLink(){
  cardSave();
  setupESP8266();
  connectToWiFi();
  sendPOSTRequest();
  check();
}

void atCommand(String command, int timeout) {
  esp8266.println(command);
  
  long int time = millis();

  while( (time+timeout) > millis() ) {
    while(esp8266.available()) {
      char c = esp8266.read();
      Serial.write(c);
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
      Serial.write(c);
    }
  }
}

void post(String line){
  esp8266.println(line);
  boolean save = false;

  long int time = millis();

  while( (time+6000) > millis() ) {
    while(esp8266.available()) {
      char c = esp8266.read();
      Serial.write(c);
      if(c=='>'){
        save=true;
      }
      if(save) file.print(c);
    }
  }
  file.println();
}

void closeTCPConnection() {
  atCommand("AT+CIPCLOSE", timeout);
}

void sendPOSTRequest() {
  startTCPConnection();
  atCommand("AT+CIPSEND=139", timeout);
  post(PGMSTR(info));
  closeTCPConnection();

  for(int i=0;i<4;i++){
    startTCPConnection();
    atCommand("AT+CIPSEND=138", timeout);
    post(PGMSTR((char*)pgm_read_word(&(links[i]))));
    closeTCPConnection();
  }
  
  file.close();
}
