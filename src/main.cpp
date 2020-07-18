#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>


#define TFT_DC 4
#define TFT_CS 15
#define TFT_RST 27

int hall = hallRead();
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);


void ActualizeSensors(void * parameter){
  for(;;){ // infinite loop
    hall = hallRead();
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}


void setup() 
{
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(3);
  Serial.begin(9600);

  xTaskCreate
  (
  ActualizeSensors,    // Function that should be called
  "ActualizeSensors",   // Name of the task (for debugging)
  1000,            // Stack size (bytes)
  NULL,            // Parameter to pass
  1,               // Task priority
  NULL             // Task handle
  );


}


void loop(void) 
{
  tft.fillRect(0, 0, 60, 17, ILI9341_BLACK); //Hall
  tft.fillRect(70, 40, 180, 55, ILI9341_BLACK); //Hour
  tft.fillRect(270, 0, 320, 17, ILI9341_BLACK); //battery %
  tft.fillRect(230, 220, 320, 240, ILI9341_BLACK); //Accel
  tft.fillRect(0, 130, 135, 230, ILI9341_BLACK); //heigh & temp & pressure & humidity


  tft.setCursor(70, 45); //hour
  tft.setTextSize(6);
  tft.println("14:10"); 

  tft.setTextSize(2);  //battery %
  tft.setCursor(270, 0);
  tft.println("100%");

  tft.setTextSize(2);
  tft.setCursor(230, 225);  //accel
  tft.print("16");
  tft.println("m/s^2");

  tft.setTextSize(2);  //hall
  tft.setCursor(0, 0); 
  tft.print(hall);
  tft.setTextSize(1);
  tft.println("*");

  tft.setTextSize(2);  //heigh
  tft.setCursor(0, 135); 
  tft.print("1000");
  tft.println("m a.s.l");

  tft.setTextSize(2);  //temp
  tft.setCursor(0, 165); 
  tft.print("1000");
  tft.setTextSize(1);
  tft.print("*");
  tft.setTextSize(2);
  tft.println("C");

  tft.setTextSize(2);  //heigh
  tft.setCursor(0, 195); 
  tft.print("1000");
  tft.println("hPa");

  tft.setTextSize(2);  //humidity
  tft.setCursor(0, 225); 
  tft.print("100");
  tft.println("%");
  

  delay(300);
}