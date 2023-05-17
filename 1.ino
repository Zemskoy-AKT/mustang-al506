#define potent_pin 0
#define pin_speed 10
#define pin_drive 7
#define pin_reverse 8
int val;
int fwd;
int rwd;
int logicsig;
int pwmsol1;
int pwmsol2;

void setup() {
  Serial.begin(9600);
  pinMode(pin_speed, INPUT);
  pinMode(pin_drive, INPUT);
  pinMode(pin_reverse, INPUT);
  digitalWrite(pin_speed, LOW);
  digitalWrite(pin_drive, LOW);
  digitalWrite(pin_reverse, LOW);
  
}

void loop() {
    fwd = digitalRead(pin_drive); // слушаем pin pin_drive - 7 - движение вперед
    rwd = digitalRead(pin_reverse); // слушаем pin pin_reverse - 8 - движение назад
    logicsig = digitalRead(pin_speed); // слушаем pin pin_speed - 10 - выбор диапазона шим
    val = analogRead(potent_pin); // аналоговый вход потенциометра
    val = map(val, 96, 1017, 0, 255);
    val = constrain(val, 0, 255);

// Движение Вперед + Две скорости  
    if (fwd == HIGH && logicsig == LOW) {
        val = constrain(val, 0, 125);
        pwmsol1 = val;
    }
    else if (fwd == HIGH && logicsig == HIGH) {
        val = constrain(val, 0, 255);
        pwmsol1 = val;
    }
    else pwmsol1 = 0;

// Движение Назад + Две скорости
    if (rwd == HIGH && logicsig == LOW) { 
        val = constrain(val, 0, 125);
        pwmsol2 = val;
    }
    else if (rwd == HIGH && logicsig == HIGH) {
        val = constrain(val, 0, 255);
        pwmsol2 = val;
    }
    else pwmsol2 = 0;

// Авария два высоких сигнала на FWD и RWD отключение ШИМ
    if (fwd == HIGH && rwd == HIGH) {
      pwmsol1 = 0;
      pwmsol2 = 0;
      Serial.print("Error");
    }
    analogWrite(5, pwmsol1);
    analogWrite(5, pwmsol2);
  Serial.print("FWD:");Serial.print(pwmsol1);
  Serial.print("RWD:");Serial.println(pwmsol2);
  delay(30);
  
}
