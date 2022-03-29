#include <IRremote.h> 
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);     
decode_results results;

#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3f, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

int green = 6;
int yellow = 5;
int red = 4;

int laser = 2;

int fan = 3;

int i = 0;
String info; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);     
  irrecv.enableIRIn();
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();

  pinMode(green,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(red,OUTPUT);

  pinMode(laser,OUTPUT);

  pinMode(fan,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results))// Returns 0 if no data ready, 1 if data ready.     
    {     
     irrecv.resume(); // Restart the ISR state machine and Receive the next value
      lcd.setCursor(0, 0);
      lcd.clear();

      digitalWrite(green,LOW);
      digitalWrite(yellow,LOW);
      digitalWrite(red,LOW);
      digitalWrite(laser,LOW);
      digitalWrite(fan,LOW);
      // ch-
     if (results.value==16753245){
        lcd.print("ch-");
        digitalWrite(green,HIGH);
      }
      // ch
      else if(results.value==16736925){
        lcd.print("ch");
        digitalWrite(yellow,HIGH);
        }
       // ch+
      else if(results.value==16769565){
      lcd.print("ch+");
      digitalWrite(red,HIGH);
      }
      // prev
      else if(results.value==16720605){
      lcd.print("prev");
      }
      // next
      else if(results.value==16712445){
      lcd.print("next");
      }
      // play
      else if(results.value==16761405){
      lcd.print("play");
      digitalWrite(fan,HIGH);
      }
      // -
      else if(results.value==16769055){
      lcd.print("-");
      }
      // +
      else if(results.value==16754775){
      lcd.print("+");
      }
      // eq
      else if(results.value==16748655){
      lcd.print("eq");
      digitalWrite(laser,HIGH);
      }
      // 100+
      else if(results.value==16750695){
      lcd.print("100+");
      }
      // 200+
      else if(results.value==16756815){
      lcd.print("200+");
      }
      // 0
      else if(results.value==16738455){
      lcd.print("0");
      }
      // 1
      else if(results.value==16724175){
      lcd.print("1");
      }
      // 2
      else if(results.value==16718055){
      lcd.print("2");
      }
      // 3
      else if(results.value==16743045){
      lcd.print("3");
      }
      // 4
      else if(results.value==16716015){
      lcd.print("4");
      }
      // 5
      else if(results.value==16726215){
      lcd.print("5");
      }
      // 6
      else if(results.value==16734885){
      lcd.print("6");
      }
      // 7
      else if(results.value==16728765){
      lcd.print("7");
      }
      // 8
      else if(results.value==16730805){
      lcd.print("8");
      }
      // 9
      else if(results.value==16732845){
      lcd.print("9");
      }
      else {
        lcd.print("click too fast");
      };
     
    }
    lcd.setCursor(0, 1); 
    info = i;
    info = "Count: " + info;
    lcd.print(info);
    i++;
    delay(1000);
}
