#include <Servo.h>
Servo myservo;

#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int place[] = {8, 9, 10, 11, 12, 13};
const int led[] = {0, 1, A0, A1, A2, A3, A4};
byte val[6];
const int in    = 3;
const int out   = 2;
int count = 0;
int valin = 0;
int valout = 0;
int pos = 0;
int cnt;
int y = 0;
void setup() {
  //********************Declares the input/output pins***********************************//
/*pinMode(A0,OUTPUT);
//pinMode(A1,OUTPUT);
pinMode(A2,OUTPUT);
pinMode(A3,OUTPUT);
pinMode(0,OUTPUT);
pinMode(1,OUTPUT);
*/
  for (int i = 0; i <= 5; i++)
  {
    pinMode(place[i], INPUT);
    pinMode(led[i], OUTPUT);
  }

  pinMode(in, INPUT);
  pinMode(out, INPUT);

  myservo.attach(5);
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("GP NAGPUR");
  lcd.setCursor(0, 1);
  lcd.print("ETC Department");
  myservo.write(0);

  for (pos = 0; pos <= 40; pos += 1) {
    myservo.write(pos);
    delay(30);
  }
  delay(1000);
  for (pos = 40; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(30);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  count = 0;
 
}

void loop() {
  //***************************PRINT THE PARKING LOT FREE FOR PARKING****************************//
  //*******************************************************//
  lcd.setCursor(0, 0);
  lcd.print("Park-Left:");
  
  lcd.setCursor(0, 1);
  
  for ( y = 0; y <6 ; y++)
  {
    val[y] = digitalRead(place[y]);

   
    if (val[y] == 1) {
      lcd.print(y + 1);
      delay(100);

    }
       
    }
    
  lcd.print("      ");
    lcd.setCursor(10,0 );
    lcd.print("count:");
  
    if (val[0] == 1){
        digitalWrite(0,HIGH);
      }
      else {
        digitalWrite(0,LOW);
      }
       if (val[1] == 1){
        digitalWrite(1,HIGH);
      }
      else{
           
            digitalWrite(1,LOW);
      }
           if (val[2] == 1){
        digitalWrite(A0,HIGH);
      }
      else{
     
            digitalWrite(A0,LOW);
      }
       if (val[3] == 1){
        digitalWrite(A1,HIGH);
      }
      else{
        digitalWrite(A1,LOW);
      }
            if (val[4] == 1){
        digitalWrite(A2,HIGH);
      }
      else{
        digitalWrite(A2,LOW);
      }
          if (val[5] == 1){
        digitalWrite(A3,HIGH);
      }
     else{
      digitalWrite(A3,LOW);
     }
  valin = digitalRead(in);

  valout = digitalRead(out);



  //*********************CHECK IF CAR EXIT **********************************//
  //***************************THE PARKING****************************//

  if (valout == LOW) {
    for (pos = 0; pos <= 40; pos += 1) {
      myservo.write(pos);
      delay(30);
    }

    while (valout == LOW) {
      valout = digitalRead(out);
    }
    count++;

   // if (count < 7) { }

    delay(1000);
    for (pos = 40; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(30);
    }
  }
  //********************************************************
  //******************CHECK IF CAR ENTERS*************************************//
  //*************************THE PARKING ******************************//

  if (valin == LOW) {

    myservo.attach(5);
    for (pos = 0; pos <= 40; pos += 1) {
      myservo.write(pos);
      delay(30);
    }

    while (valin == LOW) {
      valin = digitalRead(in);
    }
    count--;

    if (count <= 0) {
      count = 0;
    }

    delay(1000);
    for (pos = 40; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(30);
    }
  }
  //*******************************************************//
  //************************COUNT FULL CHECK*******************************//
      
    if (count >= 6) {
    myservo.write(0);
    delay(1000); 
    myservo.detach();
    lcd.setCursor(9, 1);
    lcd.print(" full");
  }
  else
  {
    lcd.setCursor(12, 1);
    lcd.print(count);
    lcd.setCursor(9, 1);
    lcd.print("   ");
    lcd.setCursor(13, 1);
    lcd.print("   ");
  }
}
