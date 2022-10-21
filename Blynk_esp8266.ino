// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>


//Motor PINs
#define DEN1 D0
#define DEN2 D1
#define button1 D3
#define button2 D4
boolean bt1_state=HIGH;
boolean bt2_state=HIGH;
unsigned long times=millis();
WidgetLED led_connect(V7);

void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(DEN1, OUTPUT);
  pinMode(DEN2, OUTPUT);
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  
  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
  
  if(millis()-times>1000){
    Blynk.virtualWrite(V6, millis()/1000);
    if (led_connect.getValue()){
      led_connect.off();
    }else {
      led_connect.on();
    }
    times=millis();
  }
  check_button();
}
BLYNK_WRITE(V0) {
  if(param.asInt()==1){
    digitalWrite(DEN1, LOW);
  }
  else{
    digitalWrite(DEN1, HIGH);
  }
}

BLYNK_CONNECTED() {
  // Request Blynk server to re-send latest values for all pins
  Blynk.syncAll();
  //Blynk.syncVirtual(V0, V2);
}

BLYNK_WRITE(V1) {
  if(param.asInt()==1){
    digitalWrite(DEN2, LOW);
  }
  else{
    digitalWrite(DEN2, HIGH);
  }
}

void check_button(){
  if(digitalRead(button1)==LOW){
    if(bt1_state==HIGH){
      digitalWrite(DEN1,!digitalRead(DEN1));
      Blynk.virtualWrite(V0,!digitalRead(DEN1));
      bt1_state=LOW;
      delay(200);
    }
  }else{
    bt1_state=HIGH;
  }
   if(digitalRead(button2)==LOW){
    if(bt2_state==HIGH){
      digitalWrite(DEN2,!digitalRead(DEN2));
      Blynk.virtualWrite(V1,!digitalRead(DEN2));
      bt2_state=LOW;
      delay(200);
    }
  }else{
    bt2_state=HIGH;
  }
}
