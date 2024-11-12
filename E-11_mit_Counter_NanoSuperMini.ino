// E-11 mit Zähler V3
// 24.10.2024

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <DFRobot_DF1201S.h>
#include <SoftwareSerial.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3c
#define PIN 16
#define NUMPIXELS 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial mySerial (9, 10);
DFRobot_DF1201S myDFPlayer;

const int trigger = 3;
const int change = 5;
const int recharge = 7;

int a = 100;
int fireled = 16;

int triggerstate = 0;
int lasttriggerstate = 0;
int triggercounter = 0;

int changestate = 0;
int lastchangestate = 0;
int changecounter = 1;

int rechargestate = 0;
int lastrechargestate = 0;

long lastDebounceTime = 0;
long debounceDelay = 200;
long hold = 3000;

void start(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 3);
  display.cp437(true);
  display.println(F("Powered by"));
  display.setTextSize(2);
  display.setCursor(17, 18);
  display.println(F("T.E.A.M."));
  display.display();
  delay(2000);
}

void Blastersetup(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(55, 0);
  display.cp437(true);
  display.println(F("E-11"));
  display.setCursor(80, 0);
  display.println(F("TX150868"));
  display.drawRoundRect(16, 15, 112, 17, 3, SSD1306_WHITE);
  display.display();
}

void magfull(){
  display.fillRect(20,17,111,13,SSD1306_BLACK);
  display.display();
  delay(1);
  for (int i = 118; i > 13; i -= 7){
    display.fillRect(i,17,6,13,SSD1306_WHITE);
    display.display();
    delay(a);
  }
}

void Blaster(){
  for (int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i,pixels.Color(250,0,0));
    pixels.show();
    delay(10);
    pixels.setPixelColor(i,pixels.Color(0,0,0));
    pixels.show();
  }
}

void Stun(){
  for (int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i,pixels.Color(0,0,250));
    pixels.show();
  }
  delay(100);
  pixels.clear();
  pixels.show();
}

void Mag(){
  switch (triggercounter){
    case 1:
    display.fillRect(20,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 2:
    display.fillRect(27,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 3:
    display.fillRect(34,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 4:
    display.fillRect(41,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 5:
    display.fillRect(48,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 6:
    display.fillRect(55,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 7:
    display.fillRect(62,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 8:
    display.fillRect(69,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 9:
    display.fillRect(76,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 10:
    display.fillRect(83,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 11:
    display.fillRect(90,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 12:
    display.fillRect(97,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 13:
    display.fillRect(104,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 14:
    display.fillRect(111,17,6,13,SSD1306_BLACK);
    display.display();
    break;

    case 15:
    display.fillRect(118,17,6,13,SSD1306_BLACK);
    display.display();
    break;
  }
}

void SelectorPosition(){
  switch (changecounter)
  {
  case 1:
    myDFPlayer.playFileNum(5);
    delay(10);
    Blaster();
    break;

    case 2:
    myDFPlayer.playFileNum(6);
    delay(10);
    Stun();
    break;

    case 3:
    myDFPlayer.playFileNum(7);
    delay(10);
    break;
  }
}

void Modus(){
  switch (changecounter)
  {
  case 1:
    display.fillRect(0,0,79,15,SSD1306_BLACK);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10,0);
    display.cp437(true);
    display.println(F("Blaster"));
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(55,0);
    display.cp437(true);
    display.println(F("E-11"));
    display.display();
    break;
  
  case 2:
    display.fillRect(0,0,79,15,SSD1306_BLACK);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10,0);
    display.cp437(true);
    display.println(F("Stun"));
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(55,0);
    display.cp437(true);
    display.println(F("E-11"));
    display.display();
    break;

  case 3:
    display.fillRect(0,0,79,15,SSD1306_BLACK);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10,0);
    display.cp437(true);
    display.println(F("Imp. March"));
    display.display();
    break; 
  }
}

void setup(){
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  pinMode(trigger, INPUT_PULLUP);
  pinMode(change, INPUT_PULLUP);
  pinMode(recharge, INPUT_PULLUP);
  pinMode(fireled, OUTPUT);
  digitalWrite(fireled, LOW);

  mySerial.begin(115200);
  myDFPlayer.begin(mySerial);
  myDFPlayer.setVol(30);
  delay(100);
  myDFPlayer.switchFunction(myDFPlayer.MUSIC);
  myDFPlayer.setPlayMode(myDFPlayer.SINGLE);
  myDFPlayer.enableAMP();
  delay(200);

  pixels.begin();
  pixels.clear();
  delay(10);

  display.clearDisplay();
  display.display();

  start();
  display.clearDisplay();
  display.display();
  Blastersetup();
  delay(100);
  myDFPlayer.playFileNum(1);
  magfull();
  delay(10);
}

void loop(){
  Modus();
  triggerstate = digitalRead(trigger);
  changestate = digitalRead(change);
  rechargestate = digitalRead(recharge);

  if (changestate != lastchangestate && millis() - lastDebounceTime > debounceDelay){
    if (changestate == LOW){
      myDFPlayer.playFileNum(2);
      delay(10);
      if (changecounter < 3){
        changecounter++;
      }else{
        changecounter = 1;
      }
    }
  }

  if (triggerstate != lasttriggerstate && millis() - lastDebounceTime > debounceDelay){
    if (triggerstate == LOW){
      lastDebounceTime = millis();
      if (triggercounter < 15){
        triggercounter++;
        SelectorPosition();
        Mag();
      }else{
        myDFPlayer.playFileNum(3);
        delay(10);
      }
    }else{

    }
  }
  
  if (rechargestate != lastrechargestate && millis() - lastDebounceTime > debounceDelay){
    if (rechargestate == LOW){
      triggercounter = 0;
      lastDebounceTime = millis();
      myDFPlayer.playFileNum(4);
      delay(10);
      magfull();
    }else{

    }
  }

  lastchangestate = changestate;
  lasttriggerstate = triggerstate;
  lastrechargestate = rechargestate;
}
