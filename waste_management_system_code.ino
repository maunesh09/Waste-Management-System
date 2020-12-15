
#include <Ultrasonic.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h> 
#include <ESP8266WiFi.h>

char auth[] = " *********** "; // Blynk Project Token
char ssid[] = "Maunesh"; // WiFi Name
char pass[] = "******"; //WiFi Password//


BlynkTimer timer;
int distance;
Ultrasonic ultrasonic(12, 13);

WidgetLED green(V1);
WidgetLED orange(V2);
WidgetLED red(V3);

/*
 V1,V2,V3 for LED Widgets on Blynk Cloud App
 V5 for Gauge Widget
 v6 for Webhook widget to trigger URL for Dustbin Full event
 V7 for Webhook widget to trigger URL for Dustbin about to filled event
 */

void setup()
{
  // Debug console
  Serial.begin(115200);
  Ultrasonic ultrasonic(12,13); //Ultrasonic ultrasonic(Trig,Echo);
  Blynk.begin(auth, ssid, pass);
}


void loop()
  {
  
  distance = ultrasonic.Ranging(CM);
  Serial.println(distance);
  Blynk.run();
 
  
  if(distance > 30)
  {
    green.on();
    orange.off();
    red.off();
 // Blynk.virtualWrite(V6, 0);
     
  }
  
  else if(distance < 30 && distance > 15)
  {
    green.off();
    orange.on();
    red.off();
    Blynk.virtualWrite(V7, 1);
    delay(7000);
    
  }
  
  else if(distance < 15 )
  {
    green.off();
    orange.off();
    red.on();
   Blynk.virtualWrite(V6, 1); //Triggers URl, Sends msg 
   delay(10000);    //Send a request every 10 seconds
  }
  else
  {
    green.on();
    orange.off();
    red.off();
    // Blynk.virtualWrite(V0, 0);
    delay(300);
  } 
}


BLYNK_READ(V5) //Shows Level on Gauge Widget
{
  Blynk.virtualWrite(V5, distance);
}
