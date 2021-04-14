#include <iostream>
#include "Arduino.h"
#include "Wire.h"


using namespace std;

class Sensor
{
 public:
  virtual float GererInfo();
};

class UltraSonic : public Sensor
{
 public:
  UltraSonic(const int PinNum);
  float GererInfo();
 private:
  int ValeurRead;
  int Pin;
  long duration();
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

