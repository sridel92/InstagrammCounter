/*
    LilyGo Ink Screen Series u8g2Fonts Test
    config
    board -> elect ESP32 Dev Module in the development board, and keep the other options as default.
    xxxxxx
    LILYGO_T5_V213
    

*/
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ArduinoBearSSL.h>

#define LILYGO_T5_V213
#include <boards.h>
#include <GxEPD.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>    // 2.13" b/w  form DKE GROUP
#include GxEPD_BitmapExamples
#include "qrcode70.h"

#define CONNECTION_TIMEOUT 10

//------- Replace the following! ------
char ssid[]     = "**********";      // your network SSID (name)
char password[] = "**********";      // your network key
String INSTAGRAM_ACCESS_TOKEN =  "EAAM---your code here---------------------------Jsv3iclrZBvN41qe";
String IG_USER_ID =              "----your user id here-----";
String payload = "";

unsigned long delayBetweenChecks = 60000; //mean time between api requests
unsigned long whenDueToCheck = 0;
long instaFollowersCount;
String myString;
String followers;

#define FS_NO_GLOBALS
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <U8g2_for_Adafruit_GFX.h>    // https://github.com/olikraus/u8g2
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

GxIO_Class io(SPI,  EPD_CS, EPD_DC,  EPD_RSET);
GxEPD_Class display(io, EPD_RSET, EPD_BUSY);
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

void setup(void){
    Serial.begin(115200);
    Serial.println("setup");
    delay(1000);
    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");
    int timeout_counter = 0;

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(200);
        timeout_counter++;
        if(timeout_counter >= CONNECTION_TIMEOUT*5){
        ESP.restart();
        }
    }
    
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

#if defined(LILYGO_EPD_DISPLAY_102)
    pinMode(EPD_POWER_ENABLE, OUTPUT);
    digitalWrite(EPD_POWER_ENABLE, HIGH);
#endif /*LILYGO_EPD_DISPLAY_102*/
#if defined(LILYGO_T5_V102)
    pinMode(POWER_ENABLE, OUTPUT);
    digitalWrite(POWER_ENABLE, HIGH);
#endif /*LILYGO_T5_V102*/

   SPI.begin(EPD_SCLK, EPD_MISO, EPD_MOSI);
   display.init(); // enable diagnostic output on Serial
   display.setRotation(1);
   u8g2Fonts.begin(display); 
   u8g2Fonts.setFontMode(1);                     // use u8g2 transparent mode (this is default)
   u8g2Fonts.setFontDirection(0);               // left to right (this is default)
   u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
   u8g2Fonts.setBackgroundColor(GxEPD_WHITE); // apply Adafruit GFX color
}

void loop() {

  Serial.println("loop epaper");

  Screen01();    // define font, position and text

  Screen01QR70();

  FollowersGET();     // API request, define font, position and text 
  display.update();
  delay(15000);
  }



void FollowersNumbersDisplay(){
  u8g2Fonts.setFont(u8g2_font_logisoso62_tn);
  //u8g2Fonts.setFont(u8g2_font_inb63_mn);
  uint16_t x = display.width() / 2 - 100 ; // position en largeur 0 tout a gauche
  uint16_t y = display.height() / 2 + 30;
  display.fillScreen(GxEPD_WHITE);
  display.setRotation(1);
  u8g2Fonts.setCursor(x, y);
  u8g2Fonts.print(followers);
  display.update();
  }

void Screen01(){
  display.fillScreen(GxEPD_WHITE);
  //display.fillRect(0, 0, 8, 8, GxEPD_BLACK);
  //u8g2Fonts.setFont(u8g2_font_helvR14_tf);            // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2Fonts.setFont(u8g2_font_helvR14_tf); // u8g2_font_9x15B_tr // u8g2_font_inb16_mf // u8g2_font_7x14B_tr
  uint16_t x = 100;
  uint16_t y = display.height() / 2;
  //display.setRotation(1);
  u8g2Fonts.setCursor(x, y - 25); 
  u8g2Fonts.print("OriginalStefRid");
  u8g2Fonts.setFont(u8g2_font_unifont_t_chinese2);  // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2Fonts.setCursor(x -22, y - 5);
  u8g2Fonts.print("Follow me on instagram");
  //display.update();
  }


void Screen01QR70(){
  Serial.println("loop qrcode60 ");
  //display.fillScreen(GxEPD_BLACK);
    display.fillRect(0, 0, 70, 70, GxEPD_BLACK);
  display.drawBitmap(0, 0, qrcode70, 70, 70, 1); //qrcode
  //display.update();
  }
