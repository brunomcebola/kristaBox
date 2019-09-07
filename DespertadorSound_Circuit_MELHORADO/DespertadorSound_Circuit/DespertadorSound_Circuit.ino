const int buzzer = 5; //buzzer to arduino pin 9

void setup(){
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
}

void Despertador(float frequencia){
  tone(buzzer, frequencia);  
  delay(100);        
  noTone(buzzer);    
  delay(100);        
}
void loop(){
  Despertador(523.2511);
  Despertador(523.2511);
  Despertador(174.6141);
  Despertador(523.2511);
  Despertador(349.2282);
  Despertador(349.2282);
  delay(200);
  Despertador(349.2282);
  Despertador(391.9954);
  Despertador(391.9954);
  Despertador(130.8128);
  Despertador(391.9954);
  Despertador(261.6256);
  Despertador(261.6256);
  delay(200);
  Despertador(261.6256);
}
