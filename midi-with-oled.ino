/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <MIDI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

#define LED 13    // Arduino Board LED is on Pin 13
int ledState = LOW;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int p1 = random(0,100);
int p2 = random(0,100);
int p3 = random(0,100);


void setup() {
  Serial.begin(9600);

  MIDI.begin(MIDI_CHANNEL_OMNI);// start MIDI and listen to channel "MIDI_CHANNEL"
  MIDI.setHandleClock(MyClockHandler);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

}
//  display.invertDisplay(true);
//  delay(1000);

// 128x64

void loop() {

    // Clear the buffer.
    //
    MIDI.read();

    display.clearDisplay();

    drawPercentbar( 0, 0, 50, 10,p1);

    drawPercentbar( 0, 20, 100, 15,p2);

    drawPercentbar( 0, 40, 128, 20,p3);

    display.display();

    p1++;p2++;p3++;
    if( p1 > 100) p1 =0;
    if( p2 > 100) p2 =0;
    if( p3 > 100) p3 =0;

    delay(100);

}

void MyClockHandler(void) {
  if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(LED, ledState);
}

void drawPercentbar(int x,int y, int width,int height, int progress)
{

   progress = progress > 100 ? 100 : progress;
   progress = progress < 0 ? 0 :progress;

   float bar = ((float)(width-4) / 100) * progress;

   display.drawRect(x, y, width, height, WHITE);
   display.fillRect(x+2, y+2, bar , height-4, WHITE);


  // Display progress text
  if( height >= 15){
    display.setCursor((width/2) -3, y+5 );
    display.setTextSize(1);
    display.setTextColor(WHITE);
   if( progress >=50)
     display.setTextColor(BLACK, WHITE); // 'inverted' text

     display.print(progress);
     display.print("%");
  }


}