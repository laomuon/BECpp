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
Buzzer::Buzzer(const int PinNum, const UltraSonic &ultra):Pin(PinNum),ulsn(ultra),distance_limit(10.0),statusBuzzer(1){pinMode(Pin, OUTPUT);}
Buzzer::Buzzer(const int PinNum, const UltraSonic &ultra, const float distance):Pin(PinNum),ulsn(ultra),distance_limit(distance),statusBuzzer(1){pinMode(Pin, OUTPUT);}

void Buzzer::SetStatus(int s){statusBuzzer=s;}

int Buzzer::GetStatus(){return statusBuzzer;}

void Buzzer::Ring()
{
  if (statusBuzzer){
    if (ulsn.GererInfo() <= distance_limit)
    {
      
      digitalWrite(Pin, HIGH);
    }
    else
    {
      digitalWrite(Pin, LOW);
    }
  }
  else {digitalWrite(Pin, LOW);}
}

void Buzzer::SetDistanceLim(float distance){distance_limit=distance;}

float Buzzer::GetDistanceLim(){return distance_limit;}

Button::Button(const int PinNum):pin(PinNum),etatpre(LOW),etat(LOW){}

int Button::GetEtat()
{
  etat=digitalRead(pin);
}

int Button::DetectFront()
{
  if (etat == HIGH && etatpre == LOW) 
  { 
    etatpre=etat;
    return 1;
  }
  else 
  {
    etatpre=etat;
    return 0;
  }
  
}
