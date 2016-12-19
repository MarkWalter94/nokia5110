/*  Written by Marco Ortali, for any question email me at marco.ortali@live.it
    if you want to share this library you HAVE TO put this heading.

   Version : b 1.1 (stable and tested version)
   First Upgrade : 2 may 2014
   
   Last Upgrade : 6 august 2016

   Tested With : all pic 16/18/24/dspic30/33

*/


#define HDW_SPI1 0
//#define HDW_SPI2 1
#define SFT_SPI 2
//#define RMPBL_SPI 3

/*



INIT FUNCTION
1- DEFINE MODES : SOFT_SPI (SOFTWARE SPI)
                 HARDWARE_SPI1 (HARDWARE SPI1)
                 HARDWARE_SPI2 (HARDWARE SPI2)
                 REMAPPABLE_SPI (SPI WITH REMAPPABLE PINS(advanced uC))
                 
      EXAMPLE.
              #define SOFT_SPI
              
              -INSERT THIS LINE ALSO IN THE Nokia_5110_Basics.c FILE
                 
                 
1.2 - IF DEFINED SOFT SPI: DEFINE SOFTWARE SPI PINS:
      EXAMPLE.
              sbit Nokia_MOSI at RB7_bit;
              sbit Nokia_SCL at RB1_bit;
              
              sbit Nokia_MOSI_Direction at TRISC7_bit;
              sbit Nokia_SCL_Direction at TRISB1_bit;

2 - DEFINE OTHER LCD PINS:
     EXAMPLE.
              sbit Nokia_SCE_Direction at TRISB3_bit;
              sbit Nokia_DC_Direction at TRISB2_bit;
              sbit Nokia_RST_Direction at TRISC6_bit;
              
              sbit Nokia_SCE at RB3_bit;
              sbit Nokia_DC at RB2_bit;
              sbit Nokia_RST at RC6_bit;
              
3 - INCLUDE LIBRARY
     EXAMPLE.
             #include "Nokia_5110_Advance.h"
             
4 - ONLY AFTER THESE STEPS YOU CAN INITIALIZE THE LIBRARY WITH Nokia_Init();


*/
void Nokia_Init(int mode);



/*
THIS FUNCTION ONLY CLEAR THE BUFFER OF THE LCD, SO IF YOU WANT TO CLEAR THE LCD YOU HAVE TO DO : Nokia_Clear_Buffer(), Nokia_Refresh().
*/
void Nokia_Clear_Buffer();

/*
THIS FUNCTION PUTS A CHARACTER ON THE BUFFER ON THE POSITION DEFINED BY x AND y
*/
void Nokia_Chr(char st, int x, int y);

void Nokia_Big_Chr(char st, int x, int y);
/*
THIS FUNCTION PUTS A STRING ON THE BUFFER ON THE POSITION DEFINED BY x AND y
*/
void Nokia_Out(char text[],int x,int y );
void Nokia_Big_Out(char text[],int x,int y );

/*
THIS FUNCTION PUTS A NUMBER ON THE BUFFER ON THE POSITION DEFINED BY x AND y
*/
void Nokia_Num(long num,int x, int y);

/*
THIS FUNCTION PRINT A BITMAP - ONLY 504(LENGTH) CHAR ARRAY -
*/
void Nokia_Bitmap(char img[]);

/*
INVERTS ALL THE PIXELS OF THE LCD -HARDWARE FUNCTION-
*/
void Nokia_Invert(unsigned int inv);


/*
PRINT OUT THE BUFFER INTO THE LCD
*/
void Nokia_Refresh();

/*
INVERT THE PIXELS OF THE SELECTED CHAR (EXAMPLE TO SELECT A LETTER) - INVERT A SQUARE OF PIXELS THAT CONTAINS A LETTER
*/
void Nokia_Invert_Char(unsigned short x, unsigned short y);


char *Nokia_GetASCII();
void spiNokia(unsigned short byte);
/*
INVERT THE PIXELS OF A LINE ON THE BUFFER (EXAMPLE TO SELECT A LINE-OPTION)
*/
void Nokia_Invert_Line(unsigned short y);

/*
SLIDE TO RIGHT --> THE BUFFER (EXAMPLE TO SLIDE A PAGE YOU USE THIS 64 TIMES)
*/
void Nokia_shiftRightBuffer();

/*
IDEM TO LEFT
*/
void Nokia_shiftLeftBuffer();
unsigned short bytesimmetry(unsigned short byte);

/* 
SLIDE TO RIGHT--> ALL THE PAGE
*/
void slideToRight(int velocity);
/*
IDEM TO LEFT
*/
void slideToLeft(int velocity);

void Nokia_Big_Num(long number,unsigned short x, unsigned short y);

void itoa(int i, char b[]);

void Nokia_Set_Pixel(unsigned short x, unsigned short y);

void Nokia_Draw_Line(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1);

void Nokia_Draw_Rect(unsigned short x1, unsigned short y1, unsigned short width, unsigned short height );

void Nokia_Draw_Fill_Rect(unsigned short x, unsigned short y, unsigned short w, unsigned short h );

void Nokia_Draw_Circle(unsigned short x0, unsigned short y0, unsigned short r);

void Nokia_Draw_Fill_Circle(unsigned short x0, unsigned short y0, unsigned short r);