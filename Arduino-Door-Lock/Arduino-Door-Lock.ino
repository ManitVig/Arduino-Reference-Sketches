#include<Keypad.h>
#include<LiquidCrystal_I2C.h>
#include<Wire.h>

LiquidCrystal_I2C lcd(0x027, 16, 2);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','6','5','B'},
  {'7','8','9','C'},
  {'#','0','*','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//Variable Declarations
const int lockpin = 12;
String passcode = "0000";
String input = "";
char key;
bool toLock = false;
bool locked = true;

byte veriChar[] = {
  B00000,
  B00000,
  B00001,
  B00010,
  B10100,
  B01000,
  B00000,
  B00000
};

byte stopChar[] = {
  B00000,
  B00000,
  B01110,
  B11001,
  B10101,
  B10011,
  B01110,
  B00000
};

byte lockChar[] = {
  B00000,
  B00100,
  B01010,
  B01010,
  B01110,
  B01110,
  B01110,
  B00000
};

byte unlockChar[] = {
  B00000,
  B00100,
  B01010,
  B00010,
  B01110,
  B01110,
  B01110,
  B00000
};

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, veriChar);
  lcd.createChar(1, stopChar);
  lcd.createChar(2, lockChar);
  lcd.createChar(3, unlockChar);

  pinMode(lockpin, OUTPUT);
  digitalWrite(lockpin, HIGH);//Door Locked

  lcd.clear();
  lcd.print("Enter Passcode:");
  
}

void setPasscode(){
  lcd.clear();
  lcd.print("CurrentPasscode:");
  key = myKeypad.getKey();
  if (key){
    if (key != '*' && key != '#' && key != 'A' && key != 'B' && key != 'C' && key != 'D'){
      if (input.length() < 5){
        input = input + key;
        lcd.clear();
        lcd.print("CurrentPasscode:");
        lcd.setCursor(0,1);
        lcd.print(input);
       }else{
        lcd.clear();
        lcd.print("Only 4 Chars");
        lcd.setCursor(0,1);
        lcd.print("Allowed");        
       }
    }else if (key != '*' && key != '#' && key != 'A' && key == 'B' && key != 'C' && key != 'D'){
      if (input == passcode){
        input == "";
       lcd.clear();
  lcd.print("New Passcode:");
  key = myKeypad.getKey();
  if (key){
    if (key != '*' && key != '#' && key != 'A' && key != 'B' && key != 'C' && key != 'D'){
      if (input.length() < 5){
        input = input + key;
        lcd.clear();
        lcd.print("New Passcode:");
        lcd.setCursor(0,1);
        lcd.print(input);
       }else{
        lcd.clear();
        lcd.print("Only 4 Chars");
        lcd.setCursor(0,1);
        lcd.print("Allowed");        
       } 
    }else if (key != '*' && key != '#' && key != 'A' && key == 'B' && key != 'C' && key != 'D'){
      passcode = input;
      input = "";
      return; 
      
      }
  }
      }else{
        lcd.clear();
        lcd.print("Wrong Passcode");
        delay(1000);
        return;
      }
}
  }
}
void loop() {
  
if (locked == true){
  lcd.clear();
  lcd.print("Enter Passcode:");
}else if (locked == false){
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.write(3);
        lcd.setCursor(3,0);
        lcd.print("Unlocked");
}
  key = myKeypad.getKey();

   if (key){
    Serial.println(key);
     if (key != '*' && key != '#' && key != 'A' && key != 'B' && key != 'C' && key != 'D'){
      if (locked == true){
       if (input.length() < 5){
        input = input + key;
        lcd.clear();
        lcd.print("Passcode :");
        lcd.setCursor(0,1);
        lcd.print(input);
       }else{
        lcd.clear();
        lcd.print("Only 4 Chars");
        lcd.setCursor(0,1);
        lcd.print("Allowed");        
       }
      }else{return;}
     }else if (key == '*' && key != '#' && key != 'A' && key != 'B' && key != 'C' && key != 'D'){
      if (locked == true){
      if (input.length() < 4){
        lcd.print("Invalid");
        delay(2000);
        lcd.clear();
        input = "";
        return;
      }else if (input.length() == 4){
        if (input == passcode){
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.write(0);
          lcd.setCursor(3,0);
          lcd.print("Verified");

          delay(500);
          digitalWrite(lockpin, LOW); //unlocked
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.write(3);
          lcd.setCursor(3,0);
          lcd.print("Unlocked");
          locked = false;
          input = "";
          return;
        }else if (input != passcode){
          lcd.clear();
          lcd.setCursor(1,0);
          lcd.write(1);
          lcd.setCursor(3,0);
          lcd.print("Denied");

          delay(100);
          digitalWrite(lockpin, HIGH);
          locked = true;
          input = "";
          return;
        }
      }
      }else{return;}
     } else if (key != '*' && key == '#' && key != 'A' && key != 'B' && key != 'C' && key != 'D'){
      if (input.length() > 0){
        input.remove(input.length() - 1);
        lcd.clear();
        lcd.print("Passcode :");
        lcd.setCursor(0,1);
        lcd.print(input);
      }     
     }else if (key != '*' && key != '#' && key == 'A' && key != 'B' && key != 'C' && key != 'D'){
       setPasscode();
     }else if (key != '*' && key != '#' && key != 'A' && key != 'B' && key != 'C' && key == 'D'){
      if (locked == false){
      if (toLock == false){
        toLock = true;
        lcd.clear();
        lcd.print("Locking Door in");
        lcd.setCursor(2,1);
        lcd.print("in 2 minutes");

        delay(120000);
        digitalWrite(lockpin, HIGH);
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.write(2);
        lcd.setCursor(3,0);
        lcd.print("locked");
        delay(2000);
        toLock = false;
        return;
     } else if (toLock == true){
      toLock = false;
      lcd.print("Error try Again");
      delay(500);
      return;
     }
      }else{return;}
   }else if (key != '*' && key != '#' && key != 'A' && key != 'B' && key != 'C' && key != 'D'){
    if (toLock == true){
      toLock = false;
    }
   }
   else{
    return;
   }
   }
}
