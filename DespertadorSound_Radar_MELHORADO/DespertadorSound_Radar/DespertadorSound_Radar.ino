const int buzzer = 11; //buzzer to arduino pin 9

void setup(){
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
}

void Despertador (float frequencia){
  tone(buzzer, frequencia);   
  delay(100);        
  noTone(buzzer);    
  delay(100); 
}

void loop(){
  Despertador(739.9888);
  Despertador(739.9888);
  Despertador(739.9888);
  Despertador(739.9888);
  delay(500);
}
