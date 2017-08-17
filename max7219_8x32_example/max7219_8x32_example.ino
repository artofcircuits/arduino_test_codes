/*  
Max7219_8x32_example for Max7219 8x32 LED Matrix Display:
http://artofcircuits.com/product/max7219-8x32-red-led-matrix-module-assembled

----
Art of Circuits eShop is Pakistan’s popular electronics and kits store that sells electronics components, 
boards, kits and tools to make your electronics projects possible. Art of Circuits is located in Phase-8, 
Bahria Town Rawalpindi, and sells products across all cities of Pakistan.
Email: sales@artofcircuits.com
Web: http://artofcircuits.com
Facebook: http://www.facebook.com/artof.circuits
Phone / Text: 00 92 334 666 1248  
*/

#include <SPI.h>
#include <Adafruit_GFX.h>       // https://github.com/adafruit/Adafruit-GFX-Library
#include <Max72xxPanel.h>       // https://github.com/markruys/arduino-Max72xxPanel

int pinCS = 4; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays   = 1;

// LED Matrix Pin -> ESP8266 Pin
// Vcc            -> 5V
// Gnd            -> Gnd
// DIN            -> D11 (UNO) / MOSI 
// CS             -> D4  
// CLK            -> D13 (UNO) / CLK  

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int wait = 70; // In milliseconds

int spacer = 1;
int width  = 5 + spacer; // The font width is 5 pixels

void setup() {

    // put your setup code here, to run once:
    Serial.begin(115200);
 
  matrix.setIntensity(15); // Use a value between 0 and 15 for brightness
  matrix.setRotation(0, 1);    // The first display is position upside down
  matrix.setRotation(1, 1);    // The first display is position upside down
  matrix.setRotation(2, 1);    // The first display is position upside down
  matrix.setRotation(3, 1);    // The first display is position upside down
}

void loop() {
  matrix.fillScreen(LOW);
  delay(2000);
  display_message("Art of Circuits"); 
}

void display_message(String message){
   for ( int i = 0 ; i < width * message.length() + matrix.width() - spacer; i++ ) {
    //matrix.fillScreen(LOW);
    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically
    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < message.length() ) {
        matrix.drawChar(x, y, message[letter], HIGH, LOW, 1); // HIGH LOW means foreground ON, background off, reverse to invert the image
      }
      letter--;
      x -= width;
    }
    matrix.write(); // Send bitmap to display
    delay(wait/2);
  }
}
