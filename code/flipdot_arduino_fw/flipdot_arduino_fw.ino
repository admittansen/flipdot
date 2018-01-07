//#include <avr/io.h>
//#include <avr/interrupt.h>
#include <util/delay.h>

#define BAUD_RATE 57600

byte uart_buf[3] = {
  0, 0, 0};
byte new_bytes = 0;

byte B_PORTB = 0;
byte B_PORTC = 0;
byte B_PORTD = 0;

char SCREEN_INDEX = 'A';

byte A_CLOCK  = 13;
byte A_DATA   = 12;
byte A_LATCH  = 11;

byte B_CLOCK  = 10;
byte B_DATA   = 9;
byte B_LATCH  = 8;




static const unsigned char y_index[] =
{
  1, 4, 5, 2, 3,
  6, 7, 9, 12, 13,
  10, 11, 14, 15, 17,
  20, 21, 18, 19, 22,
  0, 0, 0, 0, 0
};


static const unsigned char x_index[] = {
  0x10, 0x08, 0x18, 0x04, 0x14, 0x0c, 0x1c, 0x12, 0x0a, 0x1a, 0x06, 0x16, 0x0e, 0x1e, 0x11, 0x09,
  0x19, 0x05, 0x15, 0x0d, 0x1d, 0x13, 0x0b, 0x1b, 0x07, 0x17, 0x0f, 0x1f, 0x10, 0x08, 0x18, 0x04,
  0x14, 0x0c, 0x1c, 0x12, 0x0a, 0x1a, 0x06, 0x16, 0x0e, 0x1e, 0x11, 0x09, 0x19, 0x05, 0x15, 0x0d,
  0x1d, 0x13, 0x0b, 0x1b, 0x07, 0x17, 0x0f, 0x1f, 0x10, 0x08, 0x18, 0x04, 0x14, 0x0c, 0x1c, 0x12,
  0x0a, 0x1a, 0x06, 0x16, 0x0e, 0x1e, 0x11, 0x09, 0x19, 0x05, 0x15, 0x0d, 0x1d, 0x13, 0x0b, 0x1b,
  0x07, 0x17, 0x0f, 0x1f, 0x10, 0x08, 0x18, 0x04, 0x14, 0x0c, 0x1c, 0x12, 0x0a, 0x1a, 0x06, 0x16,
  0x0e, 0x1e, 0x11, 0x09, 0x19, 0x05, 0x15, 0x0d, 0x1d, 0x13, 0x0b, 0x1b, 0x07, 0x17, 0x0f, 0x1f,
  0x10, 0x08, 0x18, 0x04, 0x14, 0x0c, 0x1c, 0x12,
};

static const unsigned char x_board[] = {
  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
  0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);

  pinMode(A_CLOCK, OUTPUT);
  pinMode(A_DATA, OUTPUT);
  pinMode(A_LATCH, OUTPUT);

  pinMode(B_CLOCK, OUTPUT);
  pinMode(B_DATA, OUTPUT);
  pinMode(B_LATCH, OUTPUT);


}

long timer;

void loop()
{
 
  
//  // For testing the flip dot screen without PC
//  for(int y = 0; y < 64; y++)
//  {
//      
//      for(int x = 0; x < 56; x++)
//      { 
//        if((x == 0 && y == 0)||(x == 0 && y == 50)) timer = micros();
//        pixel(x , y , 255);      
//        if((x == 0 && y == 0)||(x == 0 && y == 50)) Serial.println(micros()-timer);
//      }
//      for(int x = 0; x < 56; x++)
//      { 
//        pixel(x , y , 0);      
//      }
//      
//      delay(1);
//  } 
  
//  for(int y = 0; y < 64; y++)
//  {
//      for(int x = 0; x < 56; x++)
//      { 
//        pixel(x , y , 0);
//        
//      }
//  }
  

  if (Serial.available() >= 3)
  {

    uart_buf[0] = Serial.read(); //X data
    uart_buf[1] = Serial.read(); //Y data
    uart_buf[2] = Serial.read(); //color data

    pixel(uart_buf[0], uart_buf[1], uart_buf[2]);
  }

}

static void pixel (byte x_sane, byte y_sane, byte set)
{ 
  //TRANSFORM X and Y
  byte x = x_sane;
  byte y = y_sane;

  if ( y >= 32)
  {
    y = y - 32;
    SCREEN_INDEX = 'B';
  }
  else
  {
    SCREEN_INDEX = 'A';
  }

  if (y >= 16)
  {
    x = x + 56;
    y = y - 16;
  }

 

  //-----------------------MAGI

  B_PORTB = y_index[y & 0x1f];        //PortB is Row address

  if (set == 0xff)
  {
    /* Select X Board and B1.24 */
    B_PORTC = x_index[x];             //PortC is Column address and bit 6 is set bit
    B_PORTD = x_board[x] | 0x10;      //PortD is
  }
  else
  {
    /* Select X Board, BX.23 and B2.24 */

    //PortC is Column address and bit 6 is set bit
    B_PORTC = x_index[x] | 0x20;//= b 0010 0000

      //PortD is Column section, bit 3 and 5 is
    //.. Row HIGH/LOW side
    B_PORTD = x_board[x] | 0x4;//= b 0000 0100

  }
  
  //-----------------------
    
   

  //shift or shit out stuff

  if(SCREEN_INDEX == 'A')
  {
    my_digitalWrite_PORTB(A_LATCH, 0);
    shiftOut(A_DATA, A_CLOCK, B_PORTD);    
    shiftOut(A_DATA, A_CLOCK, B_PORTC);
    shiftOut(A_DATA, A_CLOCK, B_PORTB);
    my_digitalWrite_PORTB(A_LATCH, 1);
  }
  else if(SCREEN_INDEX == 'B')
  {
    my_digitalWrite_PORTB(B_LATCH, 0);
    shiftOut(B_DATA, B_CLOCK, B_PORTD);
    shiftOut(B_DATA, B_CLOCK, B_PORTC);
    shiftOut(B_DATA, B_CLOCK, B_PORTB);
    my_digitalWrite_PORTB(B_LATCH, 1);
  }

  

  _delay_us(20); // lämplig delay för magnetisering... kanske?
  
  // ZERO OUTE THE PORT
  char noll = 0;
  if(SCREEN_INDEX == 'A')
  {
    my_digitalWrite_PORTB(A_LATCH, 0);
    shiftOut(A_DATA, A_CLOCK, noll);
    shiftOut(A_DATA, A_CLOCK, B_PORTC);
    shiftOut(A_DATA, A_CLOCK, B_PORTB);
    my_digitalWrite_PORTB(A_LATCH, 1);

  }
  else if(SCREEN_INDEX == 'B')
  {
    my_digitalWrite_PORTB(B_LATCH, 0);
    shiftOut(B_DATA, B_CLOCK, noll);
    shiftOut(B_DATA, B_CLOCK, B_PORTC);
    shiftOut(B_DATA, B_CLOCK, B_PORTB);
    my_digitalWrite_PORTB(B_LATCH, 1);

  }
  
  _delay_us(20);
}


void shiftOut(int myDataPin, int myClockPin, byte myDataOut)
{
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i = 0;
  int pinState;


  //clear everything out just in case to
  //prepare shift register for bit shifting
  my_digitalWrite_PORTB(myDataPin, 0);
  my_digitalWrite_PORTB(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i = 7; i >= 0; i--)  
  {
    my_digitalWrite_PORTB(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1 << i) ) 
    {
      pinState = 1;
    }
    else 
    {
      pinState = 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    my_digitalWrite_PORTB(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin
    my_digitalWrite_PORTB(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    my_digitalWrite_PORTB(myDataPin, 0);
  }

  //stop shifting
  my_digitalWrite_PORTB(myClockPin, 0);

}

void my_digitalWrite_PORTB(byte pin, byte val)
{
  if(val == HIGH) //HIGH
  {
    PORTB |= 0x01 << (pin - 8);
  }
  else // LOW
  {
    PORTB &= ~(0x01 << (pin - 8));
  }
}





