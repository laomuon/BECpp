#include "lib.h"

#define LCD_ADDR (0x7c>>1)

UltraSonic::UltraSonic(const int PinNum)
{
  Pin=PinNum;
};

long UltraSonic::duration()
{
    pinMode(Pin, OUTPUT);
    digitalWrite(Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(Pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(Pin, LOW);
    pinMode(Pin, INPUT);
    long duration;
    duration = pulseIn(Pin, HIGH);
    return duration;
};

float UltraSonic::GererInfo()
{
     float RangeInCentimeters;
    RangeInCentimeters = duration() / 29.0 / 2.0;
    return RangeInCentimeters;
};

TempSensor::TempSensor(const int PinNum)
{
  Pin=PinNum;
}

float TempSensor::ReadPin()
{
  ValeurRead=analogRead(Pin);
  return ValeurRead;
}

float TempSensor::GererInfo()
{ 
  return ( ValeurRead * 3.3 / 1024.0)/0.07; 

}

Buzzer::Buzzer(const int PinNum, const UltraSonic &ultra):Pin(PinNum),ulsn(ultra){pinMode(Pin, OUTPUT);}

void Buzzer::Ring()
{
  if (ulsn.GererInfo() <= 10.0)
  {
    
    digitalWrite(Pin, HIGH);
  }
  else
  {
    digitalWrite(Pin, LOW);
  }
}
