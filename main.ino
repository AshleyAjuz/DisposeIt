//libraries
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>

//pin assignments
#define audioRx 0
#define audioTx 1
#define button 2
#define rotaryOutputA 5
#define rotaryOutputB 6
#define forceResistor 4

//library instantiations
SoftwareSerial mySoftwareSerial(audioRx, audioTx);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//variables
boolean rotaryOutputALast;
boolean rotaryOutputBLast;

//class definitions
class CompostIt {
  private:
  public:
};

class RecycleIt {
  private:
  public:
  boolean action();
};

class TrashIt {
  private:
  public:
};

class Audio {
  private:
  public:
 };

class GameFunctions {
  private:
  public:
 };

class Score {
  private:
  
  public:
    void incrementScore();
    void checkScore();
 };

class Timer {
  private:
  public:
};

class ScreenDisplay {
  private:
  public:
};

class Commands {
  private:
  public:
    void randomCommand();
    void checkCommand();
};

//function definitions
boolean RecycleIt::action(){
  boolean outputA = digitalRead(rotaryOutputA);
  boolean outputB = digitalRead(rotaryOutputB);

  if((outputA != rotaryOutputALast) or (outputB != rotaryOutputBLast))
    return true;
  else
    return false;
}

//object instantiation
RecycleIt recycleit;

void setup() {
  //pin mode setup
  pinMode(button, INPUT);
  pinMode(forceResistor, INPUT);
  pinMode(rotaryOutputA, INPUT);
  pinMode(rotaryOutputB, INPUT);

  //lcd setup
  lcd.begin(0x27, 16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("DisposeIt");

  //rotary start state
  digitalWrite(rotaryOutputA, HIGH);
  digitalWrite(rotaryOutputB, HIGH);
  rotaryOutputALast = HIGH;
  rotaryOutputBLast = HIGH;
}

void loop() {
  //polling for recycle
  boolean recycleItAction = recycleit.action();

  if (recycleItAction) {
    lcd.clear();
    lcd.print("Recycled!");
    delay(1000);
  }else
    lcd.clear();
  
}
