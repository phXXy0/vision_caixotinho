#include<LiquidCrystal.h>
#include <Servo.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte rel[] = {
  B00100,
  B01110,
  B10101,
  B10111,
  B10001,
  B10001,
  B01010,
  B00100
};
byte lixo[] = {
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111,
  B11111
};
byte ERRO[] = {
  B10001,
  B10001,
  B01010,
  B00100,
  B00100,
  B01010,
  B10001,
  B10001
};
Servo servo_1;
Servo servo_2;
Servo servo_3;
int STOP = 0;
int trigPin = 13;
int echoPin1 = 22;
int echoPin2 = 23;
int echoPin3 = 24;
int button1 = 8;
int button2 = 9;
int button3 = 10;
int buttonState;
int pos;
int duracao;
int dist;
int pinoRX = 37;
int pinoTX = 36;
int Pot = A13;
int tempo = 0;
int buzzer = 53;
int per1 = 0;
int per2 = 0;
int per3 = 0;
char z;
int cont1 = 0;
int cont2 = 0;
int cont3 = 0;

void setup() {
  servo_1.write(150);
  servo_2.write(150);
  servo_3.write(150);
  lcd.begin(16, 2);
  lcd.createChar(0, rel);
  lcd.createChar(1, lixo);
  lcd.createChar(2, ERRO);
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(Pot, INPUT);
  servo_1.attach(26);
  servo_2.attach(27);
  servo_3.attach(28);

}

void loop() {
  if (STOP != 1)
  {
    Timing();
    LCDset();
    ContAzul();
    ContAmarelo();
    ContVerde();
    BT();
  }
  else {
    z = Serial.read();
    BT();
  }
}


void LCDset() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pronto a abrir !");
  lcd.setCursor(0, 1);
  lcd.write(byte(0));
  lcd.print(tempo / 1000);
  lcd.print("s");
  lcd.setCursor(4, 1);
  lcd.write(byte(1));
  if (per3 >= 0 && per3 <= 100)
    lcd.print(per3);
  else {
    lcd.write(byte(2));
    lcd.write(byte(2));
  }
  lcd.setCursor(8, 1);
  lcd.write(byte(1));
  if (per2 >= 0 && per2 <= 100)
    lcd.print(per2);
  else {
    lcd.write(byte(2));
    lcd.write(byte(2));
  }
  lcd.setCursor(12, 1);
  lcd.write(byte(1));
  if (per1 >= 0 && per1 <= 100)
    lcd.print(per1);
  else {
    lcd.write(byte(2));
    lcd.write(byte(2));
  }
}

void Timing() {
  int x = analogRead(Pot);
  if (x < 200) {
    tempo = 5000;
  }
  if (x >= 200 && x < 400) {
    tempo = 10000;
  }
  if (x >= 400 && x < 600) {
    tempo = 15000;
  }
  if (x >= 600 && x < 650) {
    tempo = 20000;
  }
  if (x >= 700) {
    tempo = 25000;
  }
}

void ContAzul() {
  Sensor_de_Capacidade1();
  Cervo_Azul();
}


void ContAmarelo() {
  Sensor_de_Capacidade2();
  Cervo_Amarelo();
}
void ContVerde() {
  Sensor_de_Capacidade3();
  Cervo_Verde();
}





void Cervo_Verde() {
  buttonState = digitalRead(button1);
  if (buttonState == HIGH) {
    for (int pos = 150; pos >= 40; pos -= 1) {
      servo_1.write(pos);
      delay(15);
    }
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("CONTENTOR");
    lcd.setCursor(2, 1);
    lcd.print("VERDE ABERTO!");
    delay(tempo);
    lcd.clear();
    for (int pos = 40; pos <= 150; pos += 1) {
      servo_1.write(pos);
      delay(15);
    }
  }
}






void Cervo_Azul() {
  buttonState = digitalRead(button2);
  if (buttonState == HIGH) {
    for (int pos = 150; pos >= 40; pos -= 1) {
      servo_2.write(pos);
      delay(15);
    }
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("CONTENTOR");
    lcd.setCursor(3, 1);
    lcd.print("AZUL ABERTO!");
    delay(tempo);
    lcd.clear();
    for (int pos = 40; pos <= 150; pos += 1) {
      servo_2.write(pos);
      delay(15);
    }
  }
}


void Cervo_Amarelo() {
  buttonState = digitalRead(button3);
  if (buttonState == HIGH) {
    for (int pos = 150; pos >= 40; pos -= 1) {
      servo_3.write(pos);
      delay(15);
    }
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("CONTENTOR");
    lcd.setCursor(2, 1);
    lcd.print("AMARELO ABERTO!");
    delay(tempo);
    lcd.clear();
    for (int pos = 40; pos <= 150; pos += 1) {
      servo_3.write(pos);
      delay(15);
    }
  }
}



void Sensor_de_Capacidade1() {
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin1, HIGH);
  dist = duracao * 0.034 / 2;
  per1 = 100 - (dist / 0.217);
  if (per1 >= 85) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("CONTENTOR");
    lcd.setCursor(2, 1);
    lcd.print("VERDE CHEIO!");
    if (cont1 < 5) {
      tone(buzzer, 500);
    }
    delay(1000);
    noTone(buzzer);
    cont1 = cont1 + 1;
  }
  if (per1 < 85)
    cont1 = 0;
}
void Sensor_de_Capacidade2() {
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin2, HIGH);
  dist = duracao * 0.034 / 2;
  per2 = 100 - (dist / 0.217);
  if (per2 >= 85) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("CONTENTOR");
    lcd.setCursor(3, 1);
    lcd.print("AZUL CHEIO!");
    if (cont2 < 5) {
      tone(buzzer, 500);
    }
    delay(1000);
    noTone(buzzer);
    cont2 = cont2 + 1;
  }

  if (per2 < 85)
    cont2 = 0;
}
void Sensor_de_Capacidade3() {
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin3, HIGH);
  dist = duracao * 0.034 / 2;
  per3 = 100 - (dist / 0.217);
  if (per3 >= 85) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("CONTENTOR");
    lcd.setCursor(2, 1);
    lcd.print("AMARELO CHEIO!");
    if (cont3 < 5) {
      tone(buzzer, 500);
    }
    delay(1000);
    noTone(buzzer);
    cont3 = cont3 + 1;
  }

  if (per3 < 85)
    cont3 = 0;
}

void BT() {
  if (Serial.available() > 0)
  {
    char eco = Serial.read();
    switch (eco)
    {
      case 'a': {
          Serial.println("A abrir contentor amarelo...");
          for (int pos = 150; pos >= 40; pos -= 1) {
            servo_3.write(pos);
            delay(15);
          }
          delay(tempo);
          for (int pos = 40; pos <= 150; pos += 1) {
            servo_3.write(pos);
            delay(15);
          }
        }
        break;
      case 'b': {
          Serial.println("A abrir contentor azul...");
          for (int pos = 150; pos >= 40; pos -= 1) {
            servo_2.write(pos);
            delay(15);
          }
          delay(tempo);
          for (int pos = 40; pos <= 150; pos += 1) {
            servo_2.write(pos);
            delay(15);
          }
        }
        break;
      case 'c': {
          Serial.println("A abrir contentor verde...");
          for (int pos = 150; pos >= 40; pos -= 1) {
            servo_1.write(pos);
            delay(15);
          }
          delay(tempo);
          for (int pos = 40; pos <= 150; pos += 1) {
            servo_1.write(pos);
            delay(15);
          }
        }
        break;
      case 'd': {
          Serial.println("A abrir todos os contentores...");
          for (int pos = 150; pos >= 40; pos -= 1) {
            servo_1.write(pos);
            servo_2.write(pos);
            servo_3.write(pos);
            delay(15);
          }
          delay(tempo);
          for (int pos = 40; pos <= 150; pos += 1) {
            servo_1.write(pos);
            servo_2.write(pos);
            servo_3.write(pos);
            delay(15);
          }
        }
        break;
      case 'e': {
          delay(500);
          Serial.println("ESTADO DOS CONTENTORES:");
          Serial.println("--------------------");
          Serial.print("Contentor Amarelo a:");
          Serial.print(per3);
          Serial.println("%");
          Serial.print("Contentor Verde a:");
          Serial.print(per1);
          Serial.println("%");
          Serial.print("Contentor Azul a:");
          Serial.print(per2);
          Serial.println("%");
          Serial.println("--------------------");
          delay (500);
        }
        break;
      case 'f': {
          Serial.println("Contentores cheios... A bloquear ecoponto...");
          STOP = 1;
          lcd.clear();
          lcd.setCursor(4, 0);
          lcd.print("FORA DE");
          lcd.setCursor(5, 1);
          lcd.print("SERVICO");
          Serial.println("ECOPONTO BLOQUEADO.");
          delay(1000);
        }
        break;
      case 'g': {
          STOP = 0;
          Serial.println("Ecoponto desbloqueado, a iniciar programa...");
          delay(1000);
        }
        break;
      default : break;
    }
  }

}
