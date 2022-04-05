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
#define fsr A3
#define correctLED 3
#define incorrectLED 7
#define reset 9

//library instantiations
SoftwareSerial mySoftwareSerial(audioRx, audioTx);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//variables
boolean rotaryOutputALast;
boolean rotaryOutputBLast;
boolean buttonState = LOW;
boolean resetButtonState = LOW;
boolean lastButtonState = LOW;
boolean lastResetButtonState = LOW;
boolean recycleItAction = LOW;
boolean trashItAction = LOW;
boolean compostItAction = LOW;
unsigned long lastDebounceTime = 0;
unsigned long lastResetDebounceTime = 0;
unsigned long debounceDelay = 50; 
unsigned long resetDebounceDelay = 50;
boolean gameActive = LOW;
boolean resetAction = LOW;
int fsrReading;

//class definitions
class CompostIt {
  private:
  public:
  boolean action();
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
    int score;
  public:
  void correctAction(int action);
  void startGame();
  void endGame(char* correctAnswer);
  void restartGame();
  void incrementScore();
  void checkScore();
  int getScore();
 };

class Timer {
  private:
    int startingInterval = 5000;
    int endInterval = 1000; 
    int waitingInterval;
    int decrementRatio;
    
  public:
  Timer();
  void waiting();
};

class Commands {
  private:
    int randomCommand = 0;
    int lastCommand = 0;
    //int items = 9;
    char* itemStrings[9] = {"Cardboard", "Greasy Pizza Box", "Plastic Bag","Battery", "Paper", "Diaper", "Banana Peel", "Coffee Grounds", "Egg Shells"};
    
    //trash=0
    //recycle=1
    //compost=2
    int answers[9] = {1,0,0,0,1,0,2,2,2};
    
  public:
    void generateCommand();
    boolean checkCommand(int actionTaken);
    char* getCorrectString();
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
 
 int reading = digitalRead(button);
 if (reading != lastButtonState) 
  lastDebounceTime = millis();
  

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) 
        return true;
      else
        return false;
    }
  }

  lastButtonState = reading;
}

boolean CompostIt::action(){
  fsrReading = analogRead(fsr);  
  
  if(fsrReading > 50)
    return true;
  else
    return false;
}

void Commands::generateCommand(){
   randomCommand = random(9);

   //current command different than last command
   while(randomCommand == lastCommand)
    randomCommand = random(9);
    
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

void GameFunctions::incrementScore(){
  score++;
}

int GameFunctions::getScore(){
  return score;
}

Timer::Timer(){
  waitingInterval = startingInterval;
  decrementRatio = (startingInterval-endInterval)/100;
}

void Timer::waiting() {
  delay(waitingInterval);
  waitingInterval -= decrementRatio;
}

void GameFunctions::correctAction(int action){
  lcd.clear();
  
  if(action==0){
    lcd.clear();
    lcd.print("Correct,"); 
    lcd.setCursor(0,1);
    lcd.print("trashed!");
  }else if(action == 1){
    lcd.clear();
    lcd.print("Correct,"); 
    lcd.setCursor(0,1);
    lcd.print("recycled!");
  }else if(action == 2){
    lcd.clear();
    lcd.print("Correct,"); 
    lcd.setCursor(0,1);
    lcd.print("composted!");
  }
  incrementScore();
  digitalWrite(correctLED, HIGH);
  delay(1000);

  lcd.clear();
  lcd.print("Score:");
  lcd.setCursor(0,1);
  lcd.print(score);
  delay(1000);
  
  digitalWrite(correctLED, LOW);

  if(score == 99)
    endGame("Max score");
}

void GameFunctions::endGame(char* correctAnswer){
  gameActive = LOW;

  lcd.clear();
  lcd.print("Incorrect,");
  lcd.setCursor(0,1);
  lcd.print("Game Over!");
  digitalWrite(incorrectLED, HIGH);
  delay(1000);

  lcd.clear();
  lcd.print("Correct Answer: ");
  lcd.setCursor(0,1);
  lcd.print(correctAnswer);
  delay(1000);
  
  lcd.clear();
  lcd.print("Score:");
  lcd.setCursor(0,1);
  lcd.print(score);
  delay(1000);

  lcd.clear();
  lcd.print("Press reset to");
  lcd.setCursor(0,1);
  lcd.print("start a game.");
  delay(1000);
  
  digitalWrite(incorrectLED, LOW);
}

void GameFunctions::startGame(){
  score=0;
  gameActive = HIGH;
}

void GameFunctions::restartGame(){
  //endGame();
  gameActive = LOW;

  lcd.clear();
  lcd.print("Game Reset!");
  delay(1000);
  
  lcd.clear();
  lcd.print("Score:");
  lcd.setCursor(0,1);
  lcd.print(score);
  delay(1000);

  lcd.clear();
  lcd.print("New game");
  lcd.setCursor(0,1);
  lcd.print("starting...");
  delay(1000);
  
  startGame();
}
char* Commands::getCorrectString(){
    int correctIndex = answers[randomCommand];
    if(correctIndex==0)
      return "Trash";
    else if(correctIndex==1)
      return "Recycle";
    else
      return "Compost";
}

//object instantiation
GameFunctions game;
RecycleIt recycleit;
TrashIt trashit;
CompostIt compostit;
Commands commands;
Timer timer;

void setup() {
  //pin mode setup
  pinMode(button, INPUT);
  pinMode(fsr, INPUT);
  pinMode(rotaryOutputA, INPUT);
  pinMode(rotaryOutputB, INPUT);
  pinMode(correctLED, OUTPUT);
  pinMode(incorrectLED, OUTPUT);
  pinMode(reset, INPUT);

  //lcd setup
  lcd.begin(0x27, 16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press reset to");
  lcd.setCursor(0,1);
  lcd.print("start a game.");

  //rotary start state
  digitalWrite(rotaryOutputA, HIGH);
  digitalWrite(rotaryOutputB, HIGH);
  rotaryOutputALast = HIGH;
  rotaryOutputBLast = HIGH;

  //random seed for commands
  randomSeed(analogRead(2));
}

void gameplay(){
    //generate command
    commands.generateCommand();
  
    //polling for actions
    recycleItAction = recycleit.action();
    trashItAction = trashit.action();
    compostItAction = compostit.action();
    
    while(recycleItAction == LOW and trashItAction == LOW and compostItAction == LOW and resetAction == LOW){
      recycleItAction = recycleit.action();
      trashItAction = trashit.action();
      compostItAction = compostit.action();
      resetAction = checkReset(); }
      
    if(resetAction) //just checking reset since we were hanging in a while loop
      game.restartGame();
      
    //action taken on command, checking command
    boolean actionCorrect = false;
    
    //selected recycle
    if (recycleItAction and !trashItAction and !compostItAction) {
      actionCorrect = commands.checkCommand(1);
  
      if(actionCorrect)
        game.correctAction(1);
      else{
        char* correctAnswer = commands.getCorrectString();
        game.endGame(correctAnswer);
      }
    } //selected trash
    else if (!recycleItAction and trashItAction and !compostItAction){
      actionCorrect = commands.checkCommand(0);
  
     if(actionCorrect){
        game.correctAction(0);
      }else{
        char* correctAnswer = commands.getCorrectString();
        game.endGame(correctAnswer);
      }
    } //selected compost
    else if (!recycleItAction and !trashItAction and compostItAction){
      actionCorrect = commands.checkCommand(2);
  
     if(actionCorrect){
        game.correctAction(2);
      }else{
        char* correctAnswer = commands.getCorrectString();
        game.endGame(correctAnswer);
      }
    }//no action
    else
      lcd.clear();  
}

boolean checkReset(){
  int reading = digitalRead(reset);
  if (reading != lastResetButtonState) 
  lastResetDebounceTime = millis();

  if ((millis() - lastResetDebounceTime) > resetDebounceDelay) {
    if (reading != resetButtonState) {
      resetButtonState = reading;

      if (resetButtonState == HIGH){
        if(gameActive == LOW) {//no game, well start one
          gameActive = HIGH;}

        lcd.clear();
        lcd.print("Reset");
       
        return true;
      }
      else{
        lcd.clear();
        return false;}
    }
  }

  lastResetButtonState = reading;
}

void loop() {
  boolean initialGameActive = gameActive;
  resetAction = checkReset();
  
   if(!initialGameActive and resetAction) //no game active, and reset hit .. start a game
     game.startGame();
   else if(resetAction) //reset hit in middle of game ... restart 
    game.restartGame();
  else if(initialGameActive){
    gameplay(); }//regular game play}
}
