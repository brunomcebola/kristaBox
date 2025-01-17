/*
  PINOUT DOS COMPONENTES:

    LCD I2C:
      - SCL => A5
      - SDA => A4

    RTC (CLOCK):
      - CLK => 4
      - DAT => 3
      - RST => 2

    ESP8266-01:
      - RX => 7
      - TX => 6

    SD:
      - SCK => 13
      - MISO => 12
      - MOSI => 11
      - CS => 10

    BUZZER:
      - SIGNAL => 5


  POWER DO ARDUINO:
    - VIN => +5V pilha
    - GND => GND pilha
*/

//DEFINIÇÃO DA BIBLIOTECAS NECESSÁRIAS
#include <SoftwareSerial.h>  //esp8266-01
#include <SD.h>   //módulo SD
#include <Servo.h>    //servos
#include <virtuabotixRTC.h>   //clock
#include <LiquidCrystal_I2C.h>    //LCD I2C

#define PGMSTR(x) (__FlashStringHelper*)(x)   //função auxiliar para ler a memória flash
#define SERVOUP_PIN 9     //pin de controlo do servo superior
#define SERVODOWN_PIN 8   //pin de controlo do servo inferior
#define BUZZER 5          //pin de controlo do buzzer

virtuabotixRTC relogio(2, 3, 4);  //declaração do relógio
LiquidCrystal_I2C lcd(0x27,16,2);  //declaração do LCD de 16x2
SoftwareSerial esp8266 (6, 7); //declaração do módulo de wifi
Servo servoUp;  //declaração do servo superior
Servo servoDown;  //declaração do servo inferior

File file;  //declaração da variavel para abrir ficheiros

//DEFINIÇÕES PARA LIGAÇÃO AO WIFI E SERVIDOR
String ssid = "NOS-8290";   //nome da rede
String password = "familia_onion";    //passe da rede
String server = "kristaapi.herokuapp.com";    //link do servidor

//LINKS PARA IR BUSCAR A INFO A BASE DE DADOS
const char info[] PROGMEM = {"POST /arduino/info HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

//horario de domingo
const char dom_a[] PROGMEM = {"POST /arduino/a_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char dom_b[] PROGMEM = {"POST /arduino/b_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char dom_c[] PROGMEM = {"POST /arduino/c_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char dom_d[] PROGMEM = {"POST /arduino/d_6 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

//horario de segunda
const char seg_a[] PROGMEM = {"POST /arduino/a_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char seg_b[] PROGMEM = {"POST /arduino/b_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char seg_c[] PROGMEM = {"POST /arduino/c_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char seg_d[] PROGMEM = {"POST /arduino/d_0 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

//horario de terça
const char ter_a[] PROGMEM = {"POST /arduino/a_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char ter_b[] PROGMEM = {"POST /arduino/b_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char ter_c[] PROGMEM = {"POST /arduino/c_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char ter_d[] PROGMEM = {"POST /arduino/d_1 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

//horario de quarta
const char qua_a[] PROGMEM = {"POST /arduino/a_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qua_b[] PROGMEM = {"POST /arduino/b_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qua_c[] PROGMEM = {"POST /arduino/c_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qua_d[] PROGMEM = {"POST /arduino/d_2 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

//horario de quinta
const char qui_a[] PROGMEM = {"POST /arduino/a_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qui_b[] PROGMEM = {"POST /arduino/b_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qui_c[] PROGMEM = {"POST /arduino/c_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char qui_d[] PROGMEM = {"POST /arduino/d_3 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

//horario de sexta
const char sex_a[] PROGMEM = {"POST /arduino/a_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sex_b[] PROGMEM = {"POST /arduino/b_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sex_c[] PROGMEM = {"POST /arduino/c_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sex_d[] PROGMEM = {"POST /arduino/d_4 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

//horario de sabado
const char sab_a[] PROGMEM = {"POST /arduino/a_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sab_b[] PROGMEM = {"POST /arduino/b_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sab_c[] PROGMEM = {"POST /arduino/c_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};
const char sab_d[] PROGMEM = {"POST /arduino/d_5 HTTP/1.1\r\nHost: kristaapi.herokuapp.com\r\nContent-Length: 25\r\nContent-Type: application/json\r\n\r\n{\"boxNum\":\"123abc456def\"}"};

//ARRAY DOS LINKS PARA FACIL ACESSO
PROGMEM const char * const links[] = {
  dom_a, dom_b, dom_c, dom_d, seg_a, seg_b, seg_c, seg_d, ter_a, ter_b, ter_c, ter_d, qua_a, qua_b, qua_c, qua_d, qui_a, qui_b, qui_c, qui_d, sex_a, sex_b, sex_c, sex_d, sab_a, sab_b, sab_c, sab_d 
};


//DIAS DA SEMANA
const char dom[] PROGMEM = {"Dom - "};
const char seg[] PROGMEM = {"Seg - "};
const char ter[] PROGMEM = {"Ter - "};
const char qua[] PROGMEM = {"Qua - "};
const char qui[] PROGMEM = {"Qui - "};
const char sex[] PROGMEM = {"Sex - "};
const char sab[] PROGMEM = {"Sab - "};

//ARRAY DOS DIAS DA SEMANA PARA FACIL ACESSO 
PROGMEM const char * const diasDaSemana[] = {dom, seg, ter, qua, qui, sex, sab}; 

//TEMPO DE ESPERA PELA RESPOSTA DOS COMANDOS AT
int timeout = 3000;

//INICIALIZAÇÃO DOS COMPONENTES
void setup() {
  while(!SD.begin(10)){delay(100);}   //garante que existe um cartao sd antes de iniciar a execução do programa
  esp8266.begin(9600);    //inicializa o módulo esp8266 na baud rate 9600 - correspondente à definida no módulo 
  Serial.begin(9600);   //incializa o serial monitor na baud rate 9600

  //inicializa os servos e coloca-os na posição de bloqueio
  servoUp.attach(SERVOUP_PIN);
  servoDown.attach(SERVODOWN_PIN);
  servoUp.write(65);
  servoDown.write(100);

  pinMode(BUZZER, OUTPUT);    //define o pino de controlo do buzzer
  
  lcdInit();    //incializa o lcd
  
  delay(1000);
}

//loop continuo para controlar o programa
void loop() {
  String CLhour = hora();

  //função chamada por defeito
  //verifica se é hora de tomar alguma medicação
  cardRead(CLhour, relogio.dayofweek);

  //substituição dos meds as 23h41
  if(CLhour=="23h41") subs();

  //atualização da informação às 00h15
  if(CLhour=="00h15"){
    servoUp.detach();
    servoDown.detach();
    espLink();
    servoUp.attach(SERVOUP_PIN);
    servoDown.attach(SERVODOWN_PIN);
  }

}

//ESCREVE AS HORAS E O DIA DA SEMANA NO LCD
void lcdWrite() {
  String CLhour = hora();

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(PGMSTR((char*)pgm_read_word(&(diasDaSemana[relogio.dayofweek - 1]))));  //le o dia da semana a partir da memória flash
  lcd.print(CLhour); 
}

//INICIALIZA O LCD
void lcdInit() {
  lcd.init();
  lcd.backlight();
  lcdWrite();
}

//CONTROLA O SOM DO BUZZER
void tom(float frequencia){
  tone(BUZZER, frequencia);  
  delay(100);        
  noTone(BUZZER);    
  delay(100);        
}

//CRIA O TOQUE DO ALARME
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

//OBTEM A HORA EM TEMPO REAL
String hora() {
  relogio.updateTime(); //atualiza o valor do relógio
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

  return hour;  //hora no formato __h__
}

//LE O HORARIO E VERIFICA SE É HORA DE TOMAR A MEDICAÇÃO
void cardRead(String CLhour, int DayOfWeekCL) { 
  char text[50], SDhour[10], meds[43];
  int counter=0, lines=0, dayOfWeekSD=1; //domingo = 1; segunda = 2; ... ; sexta = 6; sábado = 7
  boolean save=false, skip=true; 
  
  file=SD.open("horario.txt", FILE_READ);
  while (file.available()) {
    char c = file.read();
    if(c=='>') save=true;
    if(save){
      text[counter]=c;  //guarda o valor da linha
      counter++;  //indica o char que foi lido
    }
    if(c=='\n'){    //executa quando se chega ao fim da linha
      save=false;
      int len = strlen(text)-2;

      for(int i=0;i<5;i++) SDhour[i] = text[i+1];   //obtem a hora dessa linha
      for(int i=7;i<len;i++) meds[i-7] = text[i];   //obtem os meds dessa linha

      if(!skip){lines++;}       //obtem a linha (1-4) do dia
      if(skip){skip=false;}     //permite saltar a primeira linha do ficheiro de texto

      //executa se o horário no cartão coincidir com o horário real
      if((String)SDhour==CLhour && DayOfWeekCL==dayOfWeekSD){                
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print(meds);    //mostra os medicamentos no lcd
        
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
        
        despertador();    //o alarme dispara
        
        delay(60000);

        //repoe as posições de bloqueio dos servos
        servoUp.write(65);
        servoDown.write(100);
      }

      //reinicia o valor da linha quando se chega ao final do dia
      //incremento do dia da semana
      if(lines==4){
        lines=0;
        dayOfWeekSD++;
      }
      
      //reset das variaveis 
      for(int i = 0; i < sizeof(text);  ++i ) text[i] = (char)0;
      for(int i = 0; i < sizeof(SDhour);  ++i ) SDhour[i] = (char)0;
      for(int i = 0; i < sizeof(meds);  ++i ) meds[i] = (char)0;
      
      //reset do counter
      counter=0;
    }    
  }
  
  file.close();
           
  //repoe as horas no lcd
  lcdWrite();
  
  delay(1000);
}

//PERMITE SUBSITUIR A CAIXA DE MEDICAMENTOS
void subs() {
  servoUp.write(150);
  servoDown.write(5);
  delay(900000);      //espera durante 15min
  servoUp.write(65);
  servoDown.write(100); 
}

//FAZ RESET AO FICHEIRO ONDE E GUARDADO O HORÁRIO
void cardSave(){
  SD.remove("horario.txt");   //apaga o antigo
  file = SD.open("horario.txt", FILE_WRITE);    //cria e abre um novo
  delay(100);
}

//VERIFICA SE O HORÁRIO FOI CORRETAMENTE TRANSFERIDO
void check() {
  String file1, file2; //file1 é copiado para o file dois
  boolean valid = true;
  file = SD.open("horario.txt",FILE_READ);
  if(file.read()!='>') valid=false;     //horario correto => primeiro char '>'
  file.close();

  //define que ficheiro é que vai ser copiado
  if(valid){
    file1="horario.txt";
    file2="backup.txt";
  }
  else{
    file1="backup.txt";
    file2="horario.txt";
  }

  char line[50];
  SD.remove(file2); //apaga o ficheiro errado (file2)

  for(int i=1;i<=29;i++){   //le o ficheiro linha a linha e guarda o valor na variavel line
    int linha=1;
    int counter=0;
    file = SD.open(file1, FILE_READ);
    while(file.available()){
      char c = file.read();
      if(linha==i){   //se a linha atual (i) corresponder à linha do ficheiro o valor e guardado
        line[counter]=c;
        counter++;
      }
      if(c=='\n') linha++;
      if(linha>i)break;   //quando a linha do ficheiro é superior à linha atual (i) faz-se break do while
    }
    file.close();
    file = SD.open(file2, FILE_WRITE);
    file.print(line);     //gurda o valor da linha no file2
    Serial.print(line);
    file.close();
    for(int i = 0; i < sizeof(line);  ++i ) line[i] = (char)0;   //reinicia a var line para se obter a linha seguinte
  }
}

//CHAMA AS FUNÇÕES QUE FAZEM A LIGAÇÃO À INTERNET
void espLink(){
  cardSave();
  setupESP8266();
  connectToWiFi();
  sendPOSTRequest();
  check();
}

//CONTROLA OS PEDIDOS FEITOS PELO ESP8266
void atCommand(String command, int timeout) {
  esp8266.println(command);   //envia o comando at
  
  long int time = millis();

  while( (time+timeout) > millis() ) {
    while(esp8266.available()) {
      char c = esp8266.read();
      Serial.write(c);  //obtem a resposta e escreve no serial monitor (serve de controlo)
    }
  }
}

//FAZ RESET E DEFINE O MODO DE FUNCIONAMENTO DO MODULO WIFI
void setupESP8266() {
  atCommand("AT+RST", timeout);
  atCommand("AT+CWMODE=1", timeout);
}

//FAZ A LIGAÇÃO À INTERNET
void connectToWiFi() {
  atCommand("AT+CWJAP=\"" +ssid+"\",\"" + password + "\"", 6000);
  atCommand("AT+CIFSR", timeout);
}

//FAZ A LIGAÇÃO AO SERVIDOR
void startTCPConnection() {
  esp8266.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");
  
  long int time = millis();

  while( (time+timeout) > millis() ) {
    while(esp8266.available()) {
      char c = esp8266.read();
      Serial.write(c);    //obtem a resposta e escreve no serial monitor (serve de controlo)
    }
  }
}

//FAZ O PEDIDO PARA O SERVIDOR E GUARDA A RESPOSTA NO CARTAO SD
void post(String line){
  esp8266.println(line);
  boolean save = false;

  long int time = millis();

  while( (time+6000) > millis() ) {
    while(esp8266.available()) {
      char c = esp8266.read();
      Serial.write(c);    //obtem a resposta e escreve no serial monitor (serve de controlo)
      if(c=='>'){   //quando stream de bits corresponde a info util começa a guardar
        save=true;
      }
      if(save) file.print(c);   //escrita no ficheiro 
    }
  }
  file.println(); //adiciona um /n no fim de cada linha
}

//TERMINA A LIGAÇÃO COM O SERVIDOR
void closeTCPConnection() {
  atCommand("AT+CIPCLOSE", timeout);
}

//CONTROLA A LIGAÇÃO AO SERVIDOR E OS PEDIDOS POST ENVIADOS
void sendPOSTRequest() {
  //obtem a info médica para motivos de controlo.
  //resposta esperada = >undefined&undefined
  //em caso de erro esta linha nao existe pelo que
  //o ficheiro do horário se encontra corrompido
  //e é sunstituido pelo ficheiro backup com a info correta
  startTCPConnection();
  atCommand("AT+CIPSEND=139", timeout);
  post(PGMSTR(info));
  closeTCPConnection();

  //loop para obter o horário da medicação
  for(int i=0;i<4;i++){
    startTCPConnection();
    atCommand("AT+CIPSEND=138", timeout);
    post(PGMSTR((char*)pgm_read_word(&(links[i]))));
    closeTCPConnection();
  }
  
  file.close();
}
