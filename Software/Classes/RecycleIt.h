#define rotaryOutputA 5
#define rotaryOutputB 6

boolean rotaryOutputALast;
boolean rotaryOutputBLast;

class RecycleIt {
  private:
  public:
  boolean action();
};

boolean RecycleIt::action(){
  boolean outputA = digitalRead(rotaryOutputA);
  boolean outputB = digitalRead(rotaryOutputB);

  if((outputA != rotaryOutputALast) or (outputB != rotaryOutputBLast))
    return true;
  else
    return false;
}
