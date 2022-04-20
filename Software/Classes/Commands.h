#include <LiquidCrystal_I2C.h>

class Commands {
  private:
    int randomCommand = 0;
    int lastCommand = 0;
    char* itemStrings[25] = {"Cardboard", "Greasy Pizza Box", "Plastic Bag","Battery", "Paper", "Diaper", "Banana Peel", "Coffee Grounds", "Egg Shells", "Chip bag",
                              "Water bottle cap", "Chicken bone", "Plastic cup","Aluminum can","Glass jars", "Apple core","Vegetable oil", "Leaves","Newspaper","Water bottle","Empty ink cartridge",
                              "CDs", "Packing peanuts", "Styrofoam", "Bubble wrap"};
    
    //trash=0
    //recycle=1
    //compost=2
    int answers[25] = { 1, //Cardboard
                        0, //Greasy pizza box
                        0, //Plastic bag
                        1, //Battery
                        1, //Paper
                        0, //Diaper
                        2, //Banana peel
                        2, //Coffee grounds
                        2, //Egg shells
                        0, //Chip bag
                        0, //water bottle cap
                        0, //Chicken bone
                        0, //Plastic cup
                        1, //Aluminum can
                        1, //Glass jars
                        2, //Apple core
                        2, //Vegetable oil
                        2, //Leaves
                        1, //Newspaper
                        1, //Water bottle
                        1, //Empty ink cartridge
                        1, //CDs
                        0, //packing peanuts
                        0, //styrofoam
                        0}; //bubble wrap
    
  public:
    void generateCommand(LiquidCrystal_I2C lcd);
    boolean checkCommand(int actionTaken);
    char* getCorrectString();
};

void Commands::generateCommand(LiquidCrystal_I2C lcd){
   randomCommand = random(25);

   //current command different than last command
   while(randomCommand == lastCommand)
    randomCommand = random(25);
    
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
