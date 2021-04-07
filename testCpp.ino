    #include <ESP8266WiFi.h> 
    int sensorPin = A0;
     
    void setup() {
        Serial.begin(115200);
        Serial.println();

        WiFi.begin("Quang Phu", "12345678");

        Serial.print("Connecting");
        while (WiFi.status() != WL_CONNECTED)
        {
          delay(500);
          Serial.print(".");
        }
        Serial.println();

        Serial.print("Connected, IP address: ");
        Serial.println(WiFi.localIP()); 
        }
     
    void loop() {

     int reading = analogRead(sensorPin);  
     

     float voltage = reading * 3.3 / 1024.0; 
     

     
     float temp = voltage/0.07;
     
     //Serial.println(temp);
 
     delay(1000);
    }
