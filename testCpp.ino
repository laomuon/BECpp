    #include <ESP8266WiFi.h> 
    #include "lib.h"
    #include  "rgb_lcd.h"
  
    

    int sensorPin = A0;
    int pinButton=14;
    
    UltraSonic uls(13);
    TempSensor temp(A0);
    Buzzer buzz(12,uls,15.0);
    Button button(pinButton);
    
    const int colorR = 255;
    const int colorG = 0;
    const int colorB = 0;
    rgb_lcd lcd;  
    float distance_actuel;
    void setup() {
      lcd.begin(16, 2);
      Serial.begin(115200);
      lcd.setRGB(colorR, colorG, colorB);

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
        buzz.SetDistanceLim(10);
        }

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
        lcd.setRGB(0,255,0);
        buzz.SetStatus(0);
      }
      else {
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
