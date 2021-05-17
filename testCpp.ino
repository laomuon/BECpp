    #include <ESP8266WiFi.h> 
    #include "lib.h"
    #include  "rgb_lcd.h"
  
    
    //Les numéros des pins où on va brancher nos composants
    //Si l'on souhaite de changer l'endroit où on les branche on peut redéfinir içi
    //Faites l'attention, le lcd ne marche que avec des portes I2C
    int sensorPin = A0;
    int pinButton=14;
    int ultrapin=13;
    int buzzpin=12;
    
    UltraSonic uls(ultrapin);
    TempSensor temp(A0);
    Buzzer buzz(buzzpin,uls,15.0);
    Button button(pinButton);
    
    
    rgb_lcd lcd;  
    float distance_actuel;
    void setup() {
      //Set LCD to 16 colones and 2 lines
      lcd.begin(16, 2);
      Serial.begin(115200);
      lcd.setRGB(255, 0, 0);

    // Print a message to the LCD.
      lcd.print("hello, world!");

      delay(1000);
       /* Serial.println();
        
        WiFi.mode(WIFI_STA);
        WiFi.begin("Nokia 6", "88888888");

        Serial.print("Connecting");
        while (WiFi.status() != WL_CONNECTED)
        {
          delay(500);
          Serial.print(".");
        }
        Serial.println();

        Serial.print("Connected, IP address: ");
        Serial.println(WiFi.localIP()); */
        
        
        //Définir la distance limite pour déclencher le buzzer comme 10cm
        buzz.SetDistanceLim(10);
        }

    //La méthode pour faire clignoter l'écran aux couleurs différents
    void breath(unsigned char color) {

    for (int i = 0; i < 255; i++) {
        lcd.setPWM(color, i);
        //delay(1);
    }

    //delay(100);
    for (int i = 254; i >= 0; i--) {
        lcd.setPWM(color, i);
        //delay(1);
    }

    //delay(100);
}
     
    void loop() {

     
    lcd.clear();
    
    button.GetEtat();
    if (button.DetectFront() == 1)
    { 
      
      if (buzz.GetStatus())
      {
        //Change à vert quand on déactive le buzzer
        lcd.setRGB(0,255,0);
        buzz.SetStatus(0);
      }
      else {
        //Change à rouge quand on réactive le buzzer
        lcd.setRGB(255,0,0);
        buzz.SetStatus(1);
        }
    }
    //Serial.println(uls.GererInfo());
    distance_actuel=uls.GererInfo();
    buzz.Ring(distance_actuel);
    lcd.setCursor(0, 0);
     
    lcd.print("Distance:");
    lcd.print(distance_actuel);
    lcd.setCursor(0, 1);
    lcd.print("Temperature:");
    temp.ReadPin();
    lcd.print(temp.GererInfo());
    //breath(REG_RED);
    //breath(REG_GREEN);
    //breath(REG_BLUE);
    

    delay(500);
    }
