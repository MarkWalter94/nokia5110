/*  
    Written by Marco Ortali, for any question email me at marco.ortali@live.it
    if you want to share this library you HAVE TO put this heading.

   Version : b 1.0 
   Last Upgrade : 19 aug 2016

   Tested With : PIC18F types, dspic30, should work with all pic with minimum req of rom and ram.
   

*/

#include "Nokia_5110_Graphics.h"
#include "Nokia_5110_Graphics_Costants.h"

#define HDW_SPI1 0
//#define HDW_SPI2 1
#define SFT_SPI 2
//#define RMPBL_SPI 3

#undef HARDWARE_SPI1
#undef HARDWARE_SPI2
#undef SOFT_SPI
#undef REMAPPABLE_SPI
#undef DISPLAY_UPDOWN

void Nokia_Init(int mode)
{
 if(mode==0)
 {
  #define HARDWARE_SPI1
 }
 else if(mode==1)
 {
  #define HARDWARE_SPI2
 }
 else if(mode==2)
 {
  #define SOFT_SPI
 }
 else if(mode==3)
 {
  #define REMAPPABLE_SPI
 }

 Nokia_SCE_Direction=0;
 Nokia_DC_Direction=0;
 Nokia_RST_Direction=0;
 
#ifdef SOFT_SPI
Soft_SPI_INIT();
#define spi_defined
#endif
 /*
#ifdef REMAPPABLE_SPI
SPI_Remappable_Init_Advanced(_SPI_REMAPPABLE_MASTER_OSC_DIV4, _SPI_REMAPPABLE_DATA_SAMPLE_MIDDLE, _SPI_REMAPPABLE_CLK_IDLE_LOW, _SPI_REMAPPABLE_LOW_2_HIGH);
#define spi_defined
#endif
      */
#ifdef HARDWARE_SPI1
SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV4, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);
#define spi_defined
#endif
/*
#ifdef HARDWARE_SPI2
SPI2_Init_Advanced(_SPI_MASTER_OSC_DIV4, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);
#define spi_defined

#endif
   */
#ifndef spi_defined
#error YOU HAVE TO DEFINE AT LEAST ONE SPI MODE BETWEEN : SPI_SOFT, REMAPPABLE_SPI, HARDWARE_SPI1, HARDWARE_SPI2
#endif

 Nokia_SCE=1;
 Nokia_RST=0;
 Delay_ms(10);
 Nokia_RST=1;
 Nokia_DC=0;
 delay_ms(1);
 Nokia_SCE=0;
 DELAY_US(1);
 spiNokia(0b00100001);
 Delay_us(1);
 Nokia_SCE=1;
 Delay_us(1);
 Nokia_SCE=0;
 Delay_us(1);
 spiNokia(0b00000110);
 Nokia_SCE=1;
 Delay_us(1);

 Nokia_SCE=0;
 Delay_us(1);
 spiNokia(0b11000110);
 Nokia_SCE=1;
 Delay_us(1);

  Nokia_SCE=0;
 Delay_us(1);
 spiNokia(0b00010011);
 Nokia_SCE=1;
 Delay_us(1);

 Nokia_SCE=0;
 Delay_us(1);
 spiNokia(0b00100000);
 Nokia_SCE=1;
 Delay_us(1);
 Nokia_SCE=0;
 Delay_us(1);
 spiNokia(0b00001100);
  Nokia_SCE=1;
  delay_us(1);
}

void Nokia_Clear_Buffer()
{
 unsigned int k;
 for(k = 0; k<504; k++)
 {
  buffer[k] = 0;
 }
}
void Nokia_Big_Chr(char st, int x, int y)
{
  unsigned int pos,i;
  pos = (84*y)+(x*12);
  for(i=0;i<12;i++)
  {
    buffer[i+pos] = (BIGASCII[st-32][i*2]);
  }
  for(i=0;i<12;i++)
  {
    buffer[i+pos+84] = (BIGASCII[st-32][(i*2)+1]);

  }
}

void Nokia_Chr(char st, int x, int y)     //every character took 6bytes (5+space)  x(0-13)  y(0-5)
{
  unsigned int pos,i;
  pos = (84*y)+(x*6);
  for(i=0;i<5;i++)
  {
    buffer[i+pos] = (ASCII[st-32][i]);
  }
}

void Nokia_Big_Out(char text[],int x,int y )
{
 unsigned short i,j,len,col,lst = 0;
 len = strlen(text);
 if((len+x)<=7)
 {
 for(i=0; i<(len);i++)
 {
    Nokia_Big_Chr(text[i], x+i, y);
 }
 }
 else
 {
    col = ((len+x)/7);
    for(j=0;(j<=col)&&(j<6) ;j++)
    {
     if(j==0)
     {
       for(i=x;i<7;i++)
       {
         Nokia_Big_Chr(text[i-x+(j*7)], i, (2*j)+y);
       }
     }
     else if(j!=(col))
     {
       for(i=0;i<7;i++)
       {
         Nokia_Big_Chr(text[i-x+(j*7)], i, (2*j)+y);
       }
     }
     else
     {
       lst = (len+x)%7;
       for(i=0;i<lst;i++)
         {
           Nokia_Big_Chr(text[i-x+(j*7)], i, (2*j)+y);
         }
       }
     

    }

 }

}
void Nokia_Out(char text[],int x,int y )
{
unsigned short i,j,len,col,lst = 0;
 len = strlen(text);
 if((len+x)<=14)
 {
 for(i=0; i<(len);i++)
 {
    Nokia_Chr(text[i], x+i, y);
 }
 }
 else
 {
    col = (len+x)/14;
    for(j=0;(j<=col)&&(j<6) ;j++)
    {
     if(j==0)
     {
       for(i=x;i<14;i++)
       {
         Nokia_Chr(text[i-x], i, y);
       }
     }
     else if(j!=(col))
     {
       for(i=0;i<14;i++)
       {
         Nokia_Chr(text[i-x+(j*14)], i, j+y);
       }
     }
     else
     {
       lst = (len+x)%14;
       for(i=0;i<lst;i++)
         {
           Nokia_Chr(text[i-x+(j*14)], i, j+y);
         }
       }


    }

 }

}

void Nokia_Num(long num, int x, int y )
{
  char buf[10];
  itoa(num,&buf);
  Nokia_Out(buf,x,y);
}

void Nokia_Bitmap(char img[])
{
 unsigned int i;
 Nokia_DC=0;
 Nokia_SCE=0;
 spiNokia(0b001000000);
 Nokia_SCE=1;
 Nokia_SCE=0;
 spiNokia(0b010000000);
 Nokia_SCE=1;
 Nokia_DC=1;
 #ifdef DISPLAY_UPDOWN
 for(i=0;i<504;i++)
 {
  Nokia_SCE=0;
  spiNokia(bytesimmetry(img[503-i]));
  Nokia_SCE=1;
 }
 #else
 for(i=0;i<504;i++)
 {
  Nokia_SCE=0;
  spiNokia(img[i]);
  Nokia_SCE=1;
 }
 #endif
 Nokia_DC=0;
}

void Nokia_Invert(unsigned int inv)
{
Nokia_DC=0;
 if(inv==1)
 {
    Nokia_SCE=0;
    spiNokia(0b00001101);
    Nokia_SCE=1;
 }
 else
 {
    Nokia_SCE=0;
    spiNokia(0b00001100);
    Nokia_SCE=1;
 }

}

void Nokia_Invert_Char(unsigned short x, unsigned short y)
{
    unsigned int k;
    unsigned int pos = y*84+x*6;

    for(k = 0; k<6; k++)
    {
     buffer[pos+k] = 255- buffer[pos+k];
    }
}

void Nokia_Refresh()
{
   Nokia_Bitmap(buffer);
 }
 
 void spiNokia(unsigned short byte)
 {
  #ifdef SOFT_SPI
  Soft_Spi_Write(byte);
  #endif
  /*
  #ifdef REMAPPABLE_SPI
  SPI_Remappable_Write(byte);
  #endif  */
  #ifdef HARDWARE_SPI1
  Spi1_Write(byte);
  #endif /*
  #ifdef HARDWARE_SPI2
  Spi2_Write(byte);
  #endif */
  
 }
 
 void Nokia_Invert_Line(unsigned short y)
 {
  unsigned int mul = y*84,k = 0;
  for(k = 0; k<84;k++)
  {
    buffer[mul+k] = 255-buffer[mul+k];
  }
 }
 
 void Nokia_shiftRightBuffer()
 {
  int col, rig;
  
  for(rig=0;rig<6;rig++)
  {

   for(col=83;col>=0;col--)
   {
    buffer[rig*84] = 0;
    buffer[(rig*84)+col] = buffer[(rig*84)+col-1];
   }
  
  }
 }
 
 void Nokia_shiftLeftBuffer()
 {
  int col, rig;

  for(rig=0;rig<6;rig++)
  {

   for(col=0;col<83;col++)
   {
    buffer[rig*84+83] = 0;

    buffer[(rig*84)+col] = buffer[(rig*84)+col+1];
   }

  }
 }
 
 unsigned short bytesimmetry(unsigned short byte)
 {
     char ret=0;
     if((byte & 128)==128)
     {
      ret+=1;
     }
     if((byte & 64)==64)
     {
      ret+=2;
     }
     if((byte & 32)==32)
     {
      ret+=4;
     }
     if((byte & 16)==16)
     {
     ret+=8;
     }
     if((byte & 8)==8)
     {
      ret+=16;
     }
     if((byte & 4)==4)
     {
     ret+=32;
     }
     if((byte & 2)==2)
     {
     ret +=64;
     }
     if((byte & 1)==1)
     {
      ret+=128;
     }
     return ret;
 }
 
 void slideToRight(int velocity)
 {
  unsigned int i = 0, j = 0;
  for(i = 0; i<84/velocity; i++)
  {
   for(j = 0; j < velocity; j++)
   {
    Nokia_shiftRightBuffer();
   }
   Nokia_Refresh();
  }
 }

  void slideToLeft(int velocity)
 {
  unsigned int i = 0, j = 0;
  for(i = 0; i<84/velocity; i++)
  {
   for(j = 0; j < velocity; j++)
   {
    Nokia_shiftLeftBuffer();
   }
   Nokia_Refresh();
  }
 }
 
 void Nokia_Big_Num(long num ,unsigned short x, unsigned short y)
 {
 
  char buf[10];
  itoa(num,&buf);
  Nokia_Big_Out(buf,x,y);
 }
 
 void itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    int shifter;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    shifter = i;
    do{
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{
        *--p = digit[i%10];
        i = i/10;
    }while(i);
}

void Nokia_Set_Pixel(unsigned short x, unsigned short y)
{
       buffer[((y/8)*84)+x] |= 1<<(y%8);
}

void Nokia_Draw_Line(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2)
{
  int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

  dx=x2-x1;      /* the horizontal distance of the line */
  dy=y2-y1;      /* the vertical distance of the line */
  dxabs=abs(dx);
  dyabs=abs(dy);
  if(dx>=0)
  {
   sdx = 1;
  }
  else
  {
  sdx=-1;
  }
  if(dy>=0)
  {
   sdy = 1;
  }
  else
  {
   sdy = -1;
  }

  x=dyabs>>1;
  y=dxabs>>1;
  px=x1;
  py=y1;


  Nokia_Set_Pixel(x1,y1);
  Nokia_Set_Pixel(x2,y2);
  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
  {
    for(i=0;i<dxabs;i++)
    {
      y+=dyabs;
      if (y>=dxabs)
      {
        y-=dxabs;
        py+=sdy;
      }
      px+=sdx;
      Nokia_Set_Pixel(px,py);
    }
  }
  else /* the line is more vertical than horizontal */
  {
    for(i=0;i<dyabs;i++)
    {
      x+=dxabs;
      if (x>=dyabs)
      {
        x-=dyabs;
        px+=sdx;
      }
      py+=sdy;
      Nokia_Set_Pixel(px,py);
    }
  }
}

void Nokia_Draw_Fill_Rect(unsigned short x, unsigned short y, unsigned short w, unsigned short h )
{
        int i;
        int j;
        for (i=x; i<x+w; i++) {

                for (j=y; j<y+h; j++) {
                        Nokia_Set_Pixel(i, j);
                }
        }

     
}
void Nokia_Draw_Rect(unsigned short x, unsigned short y, unsigned short w, unsigned short h )

{
        int i;
        for (i=x; i<x+w; i++) {
                Nokia_Set_Pixel(i, y);
                Nokia_Set_Pixel(i, y+h-1);
        }
        for (i=y; i<y+h; i++) {
                Nokia_Set_Pixel(x, i);
                Nokia_Set_Pixel(x+w-1, i);
        }

}

void Nokia_Draw_Circle(unsigned short x0, unsigned short y0, unsigned short r)
{
        int f = 1 - r;
        int ddF_x = 1;
        int ddF_y = -2 * r;
        int x = 0;
        int y = r;

        Nokia_Set_Pixel(x0, y0+r);
        Nokia_Set_Pixel(x0, y0-r);
        Nokia_Set_Pixel(x0+r, y0);
        Nokia_Set_Pixel(x0-r, y0);

        while (x<y) {
                if (f >= 0) {
                        y--;
                        ddF_y += 2;
                        f += ddF_y;
                }
                x++;
                ddF_x += 2;
                f += ddF_x;

                Nokia_Set_Pixel(x0 + x, y0 + y);
                Nokia_Set_Pixel(x0 - x, y0 + y);
                Nokia_Set_Pixel(x0 + x, y0 - y);
                Nokia_Set_Pixel(x0 - x, y0 - y);

                Nokia_Set_Pixel(x0 + y, y0 + x);
                Nokia_Set_Pixel(x0 - y, y0 + x);
                Nokia_Set_Pixel(x0 + y, y0 - x);
                Nokia_Set_Pixel(x0 - y, y0 - x);

        }
}

void Nokia_Draw_Fill_Circle(unsigned short x0, unsigned short y0, unsigned short r)
{
        int f = 1 - r;
        int ddF_x = 1;
        int ddF_y = -2 * r;
        int x = 0;
        int y = r;
        int i;



        for (i=y0-r; i<=y0+r; i++) {
                Nokia_Set_Pixel(x0, i);
        }

        while (x < y) {
                if (f >= 0) {
                        y--;
                        ddF_y += 2;
                        f += ddF_y;
                }
                x++;
                ddF_x += 2;
                f += ddF_x;

                for (i=y0-y; i<=y0+y; i++) {
                        Nokia_Set_Pixel(x0+x, i);
                        Nokia_Set_Pixel(x0-x, i);
                }
                for (i=y0-x; i<=y0+x; i++) {
                        Nokia_Set_Pixel(x0+y, i);
                        Nokia_Set_Pixel(x0-y, i);
                }
        }
}