#define fsr A3

int fsrReading;

class CompostIt {
  private:
  public:
  boolean action();
};

boolean CompostIt::action(){
  fsrReading = analogRead(fsr);  
  
  if(fsrReading > 50)
    return true;
  else
    return false;
}
