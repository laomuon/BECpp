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
    int Colordef[3]={0,0,0};
    int Color[3]={0,0,0};
    int counter=0;
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
      for (int i=0; i<3;i++) {Color[i]=0;}
      Color[counter]=255;
      lcd.setRGB(Color[0], Color[1], Color[2]);
      counter++;
      if (counter >= 3) {counter=0;}
      if (buzz.GetStatus())
      {
        buzz.SetStatus(0);
      }
      else {buzz.SetStatus(1);}
    }
    Serial.println(uls.GererInfo());
    lcd.setCursor(0, 0);
     
    lcd.print("Distance:");
    lcd.print(uls.GererInfo());
    lcd.setCursor(0, 1);
    lcd.print("Temperature:");
    temp.ReadPin();
    lcd.print(temp.GererInfo());
    //breath(REG_RED);
    //breath(REG_GREEN);
    //breath(REG_BLUE);
    buzz.Ring();

    delay(100);
    }
