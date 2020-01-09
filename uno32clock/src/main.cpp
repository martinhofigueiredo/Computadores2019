#include <Arduino.h>
#include <Wire.h>

#define START_OF_DATA 0x10       //data markers
#define END_OF_DATA 0x20         //data markers
#define DEST1 0x61          //set destination I2C address (must match firmware in Colorduino module)
#define DEST2 0x62          //set destination I2C address (must match firmware in Colorduino module)
#define DEST3 0x63          //set destination I2C address (must match firmware in Colorduino module)
#define DEST4 0x64          //set destination I2C address (must match firmware in Colorduino module)
#define SCREENSIZEX 8            //num of LEDs accross
#define SCREENSIZEY 8            //num of LEDs down

byte display_byte[3][64];        //display array - 64 bytes x 3 colours 


//setup for plasma
typedef struct
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
} ColorRGB;

//update display buffer using x,y,r,g,b format
void display(byte x, byte y, byte r, byte g, byte b) {
  byte p = (y*8)+x;   //convert from x,y to pixel number in array
  display_byte[0][p] = r;
  display_byte[1][p] = g;
  display_byte[2][p] = b;
}

//send data via I2C to a client
static byte BlinkM_sendBuffer(byte addr, byte col, byte* disp_data) {
  Wire.beginTransmission(addr);
  Wire.write(START_OF_DATA);
  Wire.write(col);
  Wire.write(disp_data, 64);
  Wire.write(END_OF_DATA);
  return Wire.endTransmission();
}

//send display buffer to display 
void update_display(byte addr) {   
  BlinkM_sendBuffer(addr, 0, display_byte[0]);   
  BlinkM_sendBuffer(addr, 1, display_byte[1]);   
  BlinkM_sendBuffer(addr, 2, display_byte[2]);  
}

void setup() 
{
  Wire.begin(); // join i2c bus (address optional for master)  
}

void loop()
{
  delay(500);
  update_display(DEST1);
  update_display(DEST2);
  update_display(DEST3);
  update_display(DEST4);
}
