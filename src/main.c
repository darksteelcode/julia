/*
 *--------------------------------------
 * Program Name:
 * Author:
 * License:
 * Description:
 *--------------------------------------
*/

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers (recommended) */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>
#include <keypadc.h>

/* Put your function prototypes here */
int juliaPixel(float x, float y, int i, float cx, float cy);
int render_rough(double cx, double cy, uint8_t c1, uint8_t c2, int Iter);
int render_full(double cx, double cy, uint8_t c1, uint8_t c2, int Iter);
int start_screen();
int menu_keys();
void draw_menu();
void draw_preview(uint8_t c1, uint8_t c2, int Iter);
void wait(uint16_t ms);
void draw_color_preview();
void draw_crosshair();
void draw_iter();
char* reverse(char *s);
char* itoa(int num, char* str, int base);
/* Put all your globals here */

#define INCREMENT 0.1

//C value
double cx = 0.0;
double cy = 0.0;

//Colors
#define NUM_COLORS 10
uint8_t colors[NUM_COLORS] = {gfx_red, gfx_orange, gfx_yellow, gfx_green, gfx_blue, gfx_purple, gfx_pink, gfx_white, gfx_black, 0x2f};

//Index in colors
int c1index = 0;
int c2index = 1;

//Forground and background colors
uint8_t c1;
uint8_t c2;

//How far to render
#define xLim 160
#define yLim 240

#define ROUGH_ITER 7
#define PREVIEW_ITER 5
//Full Rendering Iterations - setable by user
int Iter = 12;

char iter_buf[20];

void main(void) {
    /* Fill in the body of the main function here */
    //Init colors
    c1 = colors[c1index];
    c2 = colors[c2index];
    //Draw the startup screen
    gfx_Begin(gfx_8bpp);
    if(start_screen()){return;};
    //Do a rough outline
    if(render_rough(cx, cy, c1, c2, ROUGH_ITER)){return;};
    //Full render
    if(render_full(cx, cy, c2, c1, Iter)){return;};
    //Wait for keypress to exit
    while (!os_GetCSC());
    gfx_End();
}

/* Put other functions here */

int start_screen(){
  //Draw Menu
  draw_menu();
  //Draw Preview in top left
  draw_preview(c1, c2, PREVIEW_ITER);
  //Handle keys - waits for key right now
  if(menu_keys()){return 1;};
  return 0;
}

int menu_keys(){
  while(true){
    kb_Scan();
    //Check for 2nd to redraw preview
    if(kb_Data[1] & kb_2nd){
      draw_preview(c1, c2, PREVIEW_ITER);
    }
    //Check for enter to start rendering
    if(kb_Data[6] & kb_Enter){wait(400);return 0;}
    //Change colors
    if(kb_Data[4] & kb_LParen){
      c1index++;
      c1index %= NUM_COLORS;
      c1 = colors[c1index];
      wait(300);
      draw_color_preview();
    };
    if(kb_Data[5] & kb_RParen){
      c2index++;
      c2index %= NUM_COLORS;
      c2 = colors[c2index];
      draw_color_preview();
      wait(300);
    };
    //Detect Arrows and adjust cx and cy
    if(kb_Data[7] & kb_Down){
      cy += INCREMENT;
      draw_crosshair();
      wait(200);
    }
    if(kb_Data[7] & kb_Up){
      cy -= INCREMENT;
      draw_crosshair();
      wait(200);
    }
    if(kb_Data[7] & kb_Left){
      cx -= INCREMENT;
      draw_crosshair();
      wait(200);
    }
    if(kb_Data[7] & kb_Right){
      cx += INCREMENT;
      draw_crosshair();
      wait(200);
    }
    //Iterations adjustments
    if(kb_Data[6] & kb_Add){
      Iter += 1;
      draw_iter();
      wait(200);
    }
    if(kb_Data[6] & kb_Sub){
      Iter -= 1;
      draw_iter();
      wait(200);
    }
    //Presets
    if(kb_Data[3] & kb_1){
      cx = 0.26;
      cy = 0.54;
      draw_preview(c1, c2, PREVIEW_ITER);
    }
    if(kb_Data[4] & kb_2){
      cx = -1.135;
      cy = 0.2475;
      draw_preview(c1, c2, PREVIEW_ITER);
    }
    if(kb_Data[5] & kb_3){
      cx = 0.3;
      cy = -0.01;
      draw_preview(c1, c2, PREVIEW_ITER);
    }
    if(kb_Data[3] & kb_4){
      cx = -1.476;
      cy = 0;
      draw_preview(c1, c2, PREVIEW_ITER);
    }
    if(kb_Data[4] & kb_5){
      cx = 0.28;
      cy = 0.008;
      draw_preview(c1, c2, PREVIEW_ITER);
    }
    if(kb_Data[5] & kb_6){
      cx = -0.79;
      cy = 0.15;
      draw_preview(c1, c2, PREVIEW_ITER);
    }
    if(kb_Data[3] & kb_7){
      cx = -0.12;
      cy = 0.77;
      draw_preview(c1, c2, PREVIEW_ITER);
    }
    if(kb_Data[4] & kb_8){
      cx = -0.0519;
      cy = 0.688;
      draw_preview(c1, c2, PREVIEW_ITER);
    }
    if(kb_Data[5] & kb_9){
      cx = 0;
      cy = 0.75;
      draw_preview(c1, c2, PREVIEW_ITER);
    }
    if(kb_Data[3] & kb_0){
      cx = -0.1;
      cy = 0.66;
      draw_preview(c1, c2, PREVIEW_ITER);
    }

  }
  return 0;
}

void draw_menu(){
  gfx_FillScreen(gfx_white);
  //Mockup preview square
  gfx_SetColor(gfx_black);
  gfx_FillRectangle(5, 15, 54, 40);
  //Preview label
  gfx_SetTextScale(1,1);
  gfx_SetTextFGColor(gfx_black);
  gfx_PrintStringXY("Preview", 5, 5);
  gfx_PrintStringXY("Color 1", 5, 65);
  gfx_PrintStringXY("Color 2", 5, 90);
  //Color preview mockup boxes
  gfx_SetColor(gfx_black);
  gfx_FillRectangle(5, 75, 54, 10);
  gfx_FillRectangle(5, 100, 54, 10);
  //Title
  gfx_SetTextFGColor(gfx_orange);
  gfx_SetTextScale(5, 5);
  gfx_PrintStringXY("Julia", 100, 20);
  //Description
  gfx_SetTextFGColor(gfx_green);
  gfx_SetTextScale(1, 1);
  gfx_PrintStringXY("A Julia Set Viewer For the TI-84+CE", 75, 60);
  //Author
  gfx_SetTextFGColor(gfx_orange);
  gfx_SetTextScale(1, 1);
  gfx_PrintStringXY("By Edward Wawrzynek", 170, 70);
  //Controls Header
  gfx_SetTextFGColor(gfx_black);
  gfx_SetTextScale(2,2);
  gfx_PrintStringXY("Controls", 120,85);
  //Control Text
  gfx_SetTextScale(1,1);
  gfx_PrintStringXY("A Julia set starts with a complex nu-", 67, 105);
  gfx_PrintStringXY("mber C, which is represented by the  ", 67, 115);
  gfx_PrintStringXY("crosshair in the preview. Use the ar-", 67, 125);
  gfx_PrintStringXY("row keys to change it and get differ-", 67, 135);
  gfx_PrintStringXY("ent fractals. Use the + and - keys to", 67, 145);
  gfx_PrintStringXY("change the number of iterations and ", 67, 155);
  gfx_PrintStringXY("detail level. Use the ( and ) keys to", 67, 165);
  gfx_PrintStringXY("cycle through the background and f-", 67, 175);
  gfx_PrintStringXY("oreground colors, respectively. Pre-", 67, 185);
  gfx_PrintStringXY("ss enter to begin rendering, and pr-", 67, 195);
  gfx_PrintStringXY("ess any key during rendering to exit.", 67, 205);
  gfx_PrintStringXY("Press 2nd to update the preview, and ", 67, 215);
  gfx_PrintStringXY("use the 0-9 keys to select a preset C.", 67, 225);
  //Preset Text in control column for completness
  gfx_PrintStringXY("Presets", 5, 140);
  gfx_PrintStringXY("Keys 0-9", 5, 150);
}

void draw_iter(){
  //Clear Area
  gfx_SetColor(gfx_white);
  gfx_FillRectangle(5, 110, 54, 25);
  gfx_SetTextFGColor(gfx_black);
  gfx_SetTextScale(1,1);
  gfx_PrintStringXY("Iters:", 5, 115);
  itoa(Iter, iter_buf,10);
  gfx_PrintStringXY(iter_buf, 5, 125);
}

void draw_color_preview(){
  //Draw Color previews boxes
  gfx_SetColor(c1);
  gfx_FillRectangle(5, 75, 54, 10);
  gfx_SetColor(c2);
  gfx_FillRectangle(5, 100, 54, 10);
}

void draw_crosshair(){
  uint16_t x;
  uint16_t y;
  x = (uint16_t)(cx*13.5) + 32;
  y = (uint16_t)(cy*6.66) + 35;
  //Draw
  gfx_SetColor(gfx_black);
  gfx_HorizLine(x-3, y, 7);
  gfx_VertLine(x,y-3,7);
}

void draw_preview(uint8_t c1, uint8_t c2, int Iter){
  uint16_t x;
  uint8_t y;
  double zx;
  double zy;
  draw_color_preview();
  draw_iter();
  //6 x 6 blocks - resolution 54 x 40 pixels
  for(x = 0; x < 27; x++){
    for(y = 0; y < 40; y++){
      zx = (((double)x)*0.074)-2.0;
      zy = (((double)y)*0.075)-1.5;
      if(juliaPixel(zx, zy, Iter, cx, cy) == 1){
        gfx_SetColor(c2);
      }
      else{
        gfx_SetColor(c1);
      }
      gfx_SetPixel(x+5, y+15);
      gfx_SetPixel(58-x, 54-y);
    }
  }
  //Draw Small crosshair indicating where the c value is
  //Convert from floating c to real location
  draw_crosshair();
}

int juliaPixel(double x, double y, int i, double cx, double cy){
  int n;
  double tempX;
  for(n = 0; n < i; n++){
    tempX = x;
    x = (x*x)-(y*y) + cx;
    y = (2.0*tempX*y) + cy;
    if((x*x) + (y*y) > 2.0){
      return 0;
    }
  }
  return 1;
}

int render_rough(double cx, double cy, uint8_t c1, uint8_t c2, int Iter){
  //4 x 4 blocks
  uint16_t x;
  uint8_t y;
  //Z value
  double zx;
  double zy;
  for(x = 0; x < xLim; x+=4){
    for(y = 0; y < yLim; y+=4){
      zx = (((double)x)*0.0125)-2.0;
      zy = (((double)y)*0.0125)-1.5;
      if(juliaPixel(zx, zy, Iter, cx, cy) == 1){
        gfx_SetColor(c1);
      }
      else{
        gfx_SetColor(c2);
      }
      gfx_FillRectangle(x, y, 4, 4);
      gfx_FillRectangle(316-x, 236-y, 4, 4);
    }
    if(os_GetCSC()){
      gfx_End();
      return 1;
    }
  }
  return 0;
}

int render_full(double cx, double cy, uint8_t c1, uint8_t c2, int Iter){
  //Per pixel render
  uint16_t x;
  uint8_t y;
  //Z value
  double zx;
  double zy;
  for(x = 0; x < xLim; x++){
    for(y = 0; y < yLim; y++){
      zx = (((double)x)*0.0125)-2.0;
      zy = (((double)y)*0.0125)-1.5;
      if(juliaPixel(zx, zy, Iter, cx, cy) == 1){
        gfx_SetColor(c1);
      }
      else{
        gfx_SetColor(c2);
      }
      gfx_SetPixel(x, y);
      gfx_SetPixel(319-x, 239-y);
    }
    if(os_GetCSC()){
      gfx_End();
      return 1;
    }
  }
  return 0;
}

void wait(uint16_t ms){
  uint16_t i;
  uint16_t cycles;
  cycles = ms/10;
  for(i = 0; i < cycles; i++){
    boot_WaitShort();
  }
}

char * reverse(char* s)
{
  int i, j;
  char c;
  i = 0;
  j = strlen(s) - 1;
  while (i < j){
    c = s[i];
    s[i] = s[j];
    s[j] = c;
    i++;
    j--;
  }
        return s;
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str);

    return str;
}
