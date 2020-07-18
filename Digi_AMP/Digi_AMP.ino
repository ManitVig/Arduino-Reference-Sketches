#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN 4

SSD1306AsciiWire oled;

int roll;
String CHName = "UNPICKED";

void setup() {
    Serial.begin(9600);
    Wire.begin();
    Wire.setClock(400000L);

    #if RST_PIN >= 0
       oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
    #else // RST_PIN >= 0
       oled.begin(&Adafruit128x64, I2C_ADDRESS);
    #endif // RST_PIN >= 0

    pinMode(A1, INPUT);

  oled.setFont(Adafruit5x7);
  oled.clear();
  oled.setCursor(50,0);
  oled.println("AMP BOX");
  oled.set2X();
  oled.println();
  oled.setCursor(5,30);
  oled.print("Class IX-A");
  delay(1000);
}

void sense(){
  int state = digitalRead(A1);
  Serial.println(state);
  if(state == 1){
    roll = random(1,51);
  }
}

void pick(){
  switch(roll){
      case 1 :
      CHName = "Aashi";
      break;
      case 2 :
      CHName = "Aditi";
      break;
      case 3 :
      CHName = "Akshat";
      break;
      case 4 :
      CHName = "Aksheta";
      break;
      case 5 :
      CHName = "Ananya";
      break;
      case 6 :
      CHName = "Anushka B";
      break;
      case 7 :
      CHName = "Anushka S";
      break;
      case 8 :
      CHName = "Aparna";
      break;
      case 9 :
      CHName = "Aayushman";
      break;
      case 10 :
      CHName = "Charvi";
      break;
      case 11 :
      CHName = "Deepanshu";
      break;
      case 12 :
      CHName = "Disha";
      break;
      case 13 :
      CHName = "Gauri";
      break;
      case 14 :
      CHName = "Gaurish";
      break;
      case 15 :
      CHName = "Himansh";
      break;
      case 16 :
      CHName = "Hriday";
      break;
      case 17 :
      CHName = "Isha";
      break;
      case 18 :
      CHName = "Jiya";
      break;
      case 19 :
      CHName = "Kanupriya";
      break;
      case 20 :
      CHName = "Kasak";
      break;
      case 21 :
      CHName = "Keshav";
      break;
      case 22 :
      CHName = "Khushi G";
      break;
      case 23 :
      CHName = "Khushi M";
      break;
      case 24 :
      CHName = "Lipika";
      break;
      case 25 :
      CHName = "Manit";
      break;
      case 26 :
      CHName = "Manvi";
      break;
      case 27 :
      CHName = "Mehul";
      break;
      case 28 :
      CHName = "Navya";
      break;
      case 29 :
      CHName = "Nishchay";
      break;
      case 30 :
      CHName = "Nishant";
      break;
      case 31 :
      CHName = "Nishtha";
      break;
      case 32 :
      CHName = "Pari";
      break;
      case 33 :
      CHName = "Prachi";
      break;
      case 34 :
      CHName = "Pragya";
      break;
      case 35 :
      CHName = "Priyanshi";
      break;
      case 36 :
      CHName = "Riya";
      break;
      case 37 :
      CHName = "Sachin";
      break;
      case 38 :
      CHName = "Saksham";
      break;
      case 39 :
      CHName = "Sanskriti";
      break;
      case 40 :
      CHName = "Saransh";
      break;
      case 41 :
      CHName = "Sarthak";
      break;
      case 42 :
      CHName = "Sukhraj";
      break;
      case 43 :
      CHName = "Udita";
      break;
      case 44 :
      CHName = "Upasna";
      break;
      case 45 :
      CHName = "Vansh";
      break;
      case 46 :
      CHName = "Vedant";
      break;
      case 47 :
      CHName = "Yajjant";
      break;
      case 48 :
      CHName = "Yash";
      break;
      case 49 :
      CHName = "Yashika";
      break;
      case 50 :
      CHName = "Yuvika";
      break;
     }
}
void loop() {
  sense();
  pick();
  oled.set1X();
  oled.setFont(Adafruit5x7);
  oled.clear();
  oled.setCursor(40,0);
  oled.println("Class IX-A");
  oled.set2X();
  oled.println();
  oled.setCursor(0,30);
  oled.print(CHName);
  delay(500);
}
