#include <LiquidCrystal_I2C.h>

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
    void generateCommand(LiquidCrystal_I2C lcd);
    boolean checkCommand(int actionTaken);
    char* getCorrectString();
};

void Commands::generateCommand(LiquidCrystal_I2C lcd){
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

char* Commands::getCorrectString(){
    int correctIndex = answers[randomCommand];
    if(correctIndex==0)
      return "Trash";
    else if(correctIndex==1)
      return "Recycle";
    else
      return "Compost";
}
