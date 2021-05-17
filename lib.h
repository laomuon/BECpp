#include <iostream>
#include "Arduino.h"
#include "Wire.h"


using namespace std;
//class mère pour nos deux détecteurs 
class Sensor
{
 public:
  virtual float ReadPin();
  virtual float GererInfo(); //Retourner les données attendues depuis les détecteurs
};

class UltraSonic : public Sensor
{
 public:
  UltraSonic(const int PinNum);
  float GererInfo();
 private:
  int ValeurRead;
  int Pin;
  float ReadPin();
};

class TempSensor : public Sensor
{
 public:
  TempSensor(const int PinNum);
  float ReadPin();
  float GererInfo();
 
 private:
  float ValeurRead;
  int Pin;
};

class Buzzer
{
  public :
    Buzzer(const int PinNum, const UltraSonic &ultra);
    Buzzer(const int PinNum, const UltraSonic &ultra,const float distant);
    void SetDistanceLim(float distance);
    float GetDistanceLim();
    void SetStatus(int s);
    int GetStatus();
    void Ring(float distance_actuel); //La méthode pour gérer le déclenchement du buzzer
  private:
    int statusBuzzer;
    int Pin;
    UltraSonic ulsn;  
    float distance_limit;
};

class Button
{
  public:
    Button(const int PinNum);
    int GetEtat();
    int DetectFront(); //Au lieu de détecter un 1 ou un 0 à l'entrée, on va détecter un front montant
  private:
    int pin;
    int etatpre;
    int etat;  
};
