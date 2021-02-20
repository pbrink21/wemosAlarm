#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//#include <BlynkSimpleEsp8266.h>
#include <String.h>


//char auth[] = "8a3eba879a354282a71cfe9b6771f7f2";
char ssid[] = "IASTATE";
char pass[] = "";

//#define BLYNK_PRINT Serial
WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "time.nist.gov", 25200, 60000);

const int buzzerPin = D3;
const int offButton = D2;

void setup() {
  Serial.begin(115200);
  Serial.println("working");
  // init the display
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(offButton, INPUT);
 // Blynk.begin(auth, ssid, pass);  // Blynk stuff
  noTone(buzzerPin);
  timeClient.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  Serial.println(timeClient.getHours());
  Serial.println(timeClient.getMinutes());
  if(timeClient.getHours() == 7) {
    Serial.println("hour matches");
    if(timeClient.getMinutes() == 05){
      Serial.println("triggering alarm");
      digitalWrite(LED_BUILTIN, HIGH); 
      Serial.println("playing alarm");
      //buzzes until off button is pressed
      while(!digitalRead(offButton)){
        alarm();
      }
      digitalWrite(LED_BUILTIN, LOW); 
      delay(6400);
    }
  }
  delay(1000);
}

void alarm(){
       //buzzes pin
        tone(buzzerPin, 200, 50);
        delay(50);
        //stops buzzing
        noTone(buzzerPin);
        delay(50);
}
