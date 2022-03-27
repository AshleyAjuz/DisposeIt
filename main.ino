#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define audioRx 0
#define audioTx 1
#define button 2
#define rotary 3
#define forceResistor 4
#define LCD_SDA A4
#define LCD_SCL A5

LiquidCrystal_I2C lcd(0x27, 16, 2);

class CompostIt {
  private:
  public:
};

class RecycleIt {
  private:
  public:
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

CompostIt compostIt;
SoftwareSerial mySoftwareSerial(audioRx, audioTx);
  
void setup() {
  pinMode(button, INPUT);
  pinMode(forceResistor, INPUT);
  pinMode(rotary, INPUT);

  lcd.begin(0x27, 16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("DisposeIt  ");
}

void loop() {
  // put your main code here, to run repeatedly:

}
