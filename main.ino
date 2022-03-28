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
boolean buttonState = LOW;
boolean recycleItAction = LOW;
boolean trashItAction = LOW;

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
  boolean action();
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
    int score = 0;
    
  public:
    void incrementScore();
    void checkScore();
    int getScore();
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
    int randomCommand = 0;
    int lastCommand = 0;
    int items = 6;
    char* itemStrings[6] = {"Cardboard", "Greasy Pizza Box", "Plastic Bag","Battery", "Paper", "Diaper"};
    
    //trash=0
    //recycle=1
    //compost=2
    int answers[6] = {1,0,0,0,1,0};
    
  public:
    void generateCommand();
    boolean checkCommand(int actionTaken);
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

boolean TrashIt::action(){
  buttonState = digitalRead(button);
  
  if(buttonState == HIGH)
    return true;
  else
    return false;
}

void Commands::generateCommand(){
   randomCommand = random(6);

   //current command different than last command
   while(randomCommand == lastCommand)
    randomCommand = random(6);
    
   lcd.clear();
   lcd.print(itemStrings[randomCommand]);

   lastCommand = randomCommand;
}

boolean Commands::checkCommand(int actionTaken){
  if(answers[randomCommand]==actionTaken)
    return true;
  else
    return false;  
}

void Score::incrementScore(){
  score++;
}

int Score::getScore(){
  return score;
}

//object instantiation
RecycleIt recycleit;
TrashIt trashit;
Commands commands;
Score score;

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

  //random seed for commands
  randomSeed(analogRead(3));
}

void loop() {

  //generate command
  commands.generateCommand();

  //polling for actions
  recycleItAction = recycleit.action();
  trashItAction = trashit.action();
  
  while(recycleItAction == LOW and trashItAction == LOW){
    recycleItAction = recycleit.action();
    trashItAction = trashit.action(); }

  //action taken on command, checking command
  boolean actionCorrect = false;
  
  //selected recycle
  if (recycleItAction and !trashItAction) {
    actionCorrect = commands.checkCommand(1);
    lcd.clear();

    if(actionCorrect){
      lcd.print("Correct, recycled!");
      score.incrementScore();
    }else
      lcd.print("Incorrect!");  
    delay(1000);
  } //selected trash
  else if (!recycleItAction and trashItAction){
    actionCorrect = commands.checkCommand(0);
    lcd.clear();

    if(actionCorrect){
      lcd.print("Correct, trashed!");
      score.incrementScore();
    }else
      lcd.print("Incorrect!");
    delay(1000);
  }//no action
  else
    lcd.clear();  

  //displaying score
  lcd.clear();
  lcd.print(score.getScore());
  delay(1000);
  
}
