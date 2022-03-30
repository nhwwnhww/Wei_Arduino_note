#include <IRremote.h> 
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
// get the data form remote    
String get; 
bool play = false;
decode_results results;


#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3f, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

// traffic light pin
int green = 6;
int yellow = 5;
int red = 4;

// laser pin
int laser = 2;

// count
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

}

String return_remote(int result) {
   // ch-
     if (results.value==16753245){
        return "ch-";
      }
      // ch
      else if(results.value==16736925){
        return "ch";
        }
       // ch+
      else if(results.value==16769565){
        return "ch+";
      }
      // prev
      else if(results.value==16720605){
        return "prev";
      }
      // next
      else if(results.value==16712445){
        return "next";
      }
      // play
      else if(results.value==16761405){
        return "play";
      }
      // -
      else if(results.value==16769055){
        return "-";
      }
      // +
      else if(results.value==16754775){
        return "+";
      }
      // eq
      else if(results.value==16748655){
        return "eq";
      }
      // 100+
      else if(results.value==16750695){
        return "100+";
      }
      // 200+
      else if(results.value==16756815){
        return "200+";
      }
      // 0
      else if(results.value==16738455){
        return "0";
      }
      // 1
      else if(results.value==16724175){
        return "1";
      }
      // 2
      else if(results.value==16718055){
        return "2";
      }
      // 3
      else if(results.value==16743045){
        return "3";
      }
      // 4
      else if(results.value==16716015){
        return "4";
      }
      // 5
      else if(results.value==16726215){
        return "5";
      }
      // 6
      else if(results.value==16734885){
        return "6";
      }
      // 7
      else if(results.value==16728765){
        return "7";
      }
      // 8
      else if(results.value==16730805){
        return "8";
      }
      // 9
      else if(results.value==16732845){
        return "9";
      }
      else {
        return "click too fast";
      };
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results))// Returns 0 if no data ready, 1 if data ready.     
    {     
     irrecv.resume(); // Restart the ISR state machine and Receive the next value
      lcd.clear();

      digitalWrite(green,LOW);
      digitalWrite(yellow,LOW);
      digitalWrite(red,LOW);
      digitalWrite(laser,LOW);

      get = return_remote(results.value);

      if (get=="play"&&!play){
        play = true;
      }
      else if (get=="play"&&play){
        play = false;
        get = "pause";
      }

      if (get=="eq"){
        digitalWrite(laser,HIGH);
      }
      
      lcd.print(get);
      
    }

    if (get=="ch"){
      digitalWrite(green,HIGH);
      digitalWrite(yellow,HIGH);
      digitalWrite(red,HIGH);
    }
    
    lcd.setCursor(0, 1); 
    info = i;
    info = "Count: " + info;
    lcd.print(info);
    delay(100);
}
