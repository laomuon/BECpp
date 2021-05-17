#include "lib.h"

#define LCD_ADDR (0x7c>>1)
//le constructeur pour notre UltraSonic
UltraSonic::UltraSonic(const int PinNum)
{
  Pin=PinNum;
};

//On va mesurer la duration du pulse recevoir par le détecteur après qu'il a envoyé un pulse au monde extérieur
//Cette duration va nous servir à calculer la distance
float UltraSonic::ReadPin()
{
    pinMode(Pin, OUTPUT);
    digitalWrite(Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(Pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(Pin, LOW);
    pinMode(Pin, INPUT);
    float duration;
    duration = pulseIn(Pin, HIGH);
    return duration;
};

//La distance en centimètre
float UltraSonic::GererInfo()
{
     float RangeInCentimeters;
    RangeInCentimeters = ReadPin() / 29.0 / 2.0;
    return RangeInCentimeters;
};

//Le constructeur de TempSensor
TempSensor::TempSensor(const int PinNum)
{
  Pin=PinNum;
}

//On lit la valeur reçoit depuis le détecteur
float TempSensor::ReadPin()
{
  ValeurRead=analogRead(Pin);
  return ValeurRead;
}

//Prend la valeur lit et retourne la température
float TempSensor::GererInfo()
{ 
  //TempSensor range = [0;70] pour 10 bits sous 3.3V
  return ( ValeurRead * 3.3 / 1024.0)/0.07; 

}
Buzzer::Buzzer(const int PinNum, const UltraSonic &ultra):Pin(PinNum),ulsn(ultra),distance_limit(10.0),statusBuzzer(1){pinMode(Pin, OUTPUT);}
Buzzer::Buzzer(const int PinNum, const UltraSonic &ultra, const float distance):Pin(PinNum),ulsn(ultra),distance_limit(distance),statusBuzzer(1){pinMode(Pin, OUTPUT);}

void Buzzer::SetStatus(int s){statusBuzzer=s;}

int Buzzer::GetStatus(){return statusBuzzer;}

void Buzzer::Ring(float distance_actuel)
{
  //On va seulement déclencher le buzzer s'il est activé
  //Sinon il reste en silence en tous cas
  if (statusBuzzer){
    //Si la distance détecté est inférieure à la distance limite
    if (distance_actuel <= distance_limit)
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

//Détecter un front montant à l'entrée du bouton
//On va comparer l'état actuel et l'état avant
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
