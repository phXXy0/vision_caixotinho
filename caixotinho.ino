#include<LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo servo_1;
Servo servo_2;
Servo servo_3;
void setup(){
  lcd.begin(16, 2);
  pinMode(,INPUT);
  pinMode(,INPUT);
  pinMode(,INPUT);
  servo_1.attach();
  servo_2.attach();
  servo_3.attach();
   
}

void loop(){
  lcd.setCursor(0,0);
 lcd.print("VERDE       AZUL");
 lcd.setCursor(5,1);
 lcd.print("AMARELO");
 Sensor_de_Capacidade();
 Contentor_Verde();
 Contentor_Azul();
 Contentor_Amarelo();
   
}






void Contentor_Verde(){
  if(button1 == HIGH){
    for (int pos = 0; pos <= 180; pos += 1) { 
    servo_1.write(pos);              
    delay(15);                       
  }
  lcd.setCursor(4,0);
  lcd.print("CONTENTOR");
  lcd.setCursor(2,1);
  lcd.print("VERDE ABERTO!");
  delay(15000);
  lcd.clear();
  for (pos = 180; pos >= 0; pos -= 1) { 
    sevo_1.write(pos);             
    delay(15);
  }
}




void Contentor_Azul(){
  if(button2 == HIGH){
    for (int pos = 0; pos <= 180; pos += 1) { 
    servo_2.write(pos);              
    delay(15);                       
  }
  lcd.setCursor(4,0);
  lcd.print("CONTENTOR");
  lcd.setCursor(3,1);
  lcd.print("AZUL ABERTO!");
  delay(15000);
  lcd.clear();
  for (pos = 180; pos >= 0; pos -= 1) { 
    servo_2.write(pos);             
    delay(15);
  }
  
}


void Contentor_Amarelo(){
  if(button3 == HIGH){
    for (int pos = 0; pos <= 180; pos += 1) { 
    servo_3.write(pos);              
    delay(15);                       
  }
  lcd.setCursor(4,0);
  lcd.print("CONTENTOR");
  lcd.setCursor(2,1);
  lcd.print("AMARELO ABERTO!");
  delay(15000);
  lcd.clear();
  for (pos = 180; pos >= 0; pos -= 1) { 
    servo_3.write(pos);             
    delay(15);
  }
}



long Sensor_de_Capacidade() {
    long duracao;
    digitalWrite (trigPin, LOW);
    delay(2);
    digitalWrite (trigPin, HIGH);
    delay(10);
    digitalWrite (trigPin, LOW);

    duracao = pulseIn(echoPin,HIGH);
    dist = duracao*0.034/2;
    if (dist<300){
    lcd.setCursor(6,0);
    lcd.print("LIXO");
    lcd.setCursor(5,1);
    lcd.print("CHEIO!");  
    }
    }


void Bluethoot(){
  
}

    
