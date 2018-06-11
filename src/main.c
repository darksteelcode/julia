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
void printText(char *text, uint8_t x, uint8_t y);
int juliaPixel(float x, float y, int i, float cx, float cy);
int promptStr(char *str, int line);
int render_rough(double cx, double cy, uint8_t c1, uint8_t c2, int Iter);
int render_full(double cx, double cy, uint8_t c1, uint8_t c2, int Iter);
/* Put all your globals here */

//How far to render
#define xLim 160
#define yLim 240

#define ROUGH_ITER 5

void main(void) {
    //C value
    double cx = 0.4;
    double cy = -0.1;
    //Forground and background colors
    uint8_t c1 = gfx_RGBTo1555(255,125,0);
    uint8_t c2 = gfx_RGBTo1555(0,0,255);
    //Rendering parameters
    int Iter = 12;
    /* Fill in the body of the main function here */

    gfx_Begin(gfx_8bpp);
    //Do a rough outline
    if(render_rough(cx, cy, c1, c2, ROUGH_ITER)){return;};
    //Full render
    if(render_full(cx, cy, c2, c1, Iter)){return;};
    //Wait for keypress to exit
    while (!os_GetCSC());
    gfx_End();
}

/* Put other functions here */
int promptStr(char *str, int line){
  kb_key_t key;
  int index = 0;
  int pKey = 0;
  while(true){
    printText(str, 0, line);
    kb_Scan();
    str[index] = '_';
    if((kb_Data[3] & kb_0) && !pKey){
      str[index] = '0';
      index ++;
      pKey = 1;
    }
    else if((kb_Data[3] & kb_1) && !pKey){
      str[index] = '1';
      index ++;
      pKey = 1;
    }
    else if((kb_Data[4] & kb_2) && !pKey){
      str[index] = '2';
      index ++;
      pKey = 1;
    }
    else if((kb_Data[5] & kb_3) && !pKey){
      str[index] = '3';
      index ++;
      pKey = 1;
    }
    else if((kb_Data[3] & kb_4) && !pKey){
      str[index] = '4';
      index ++;
      pKey = 1;
    }
     else if((kb_Data[4] & kb_5) && !pKey){
      str[index] = '5';
      index ++;
      pKey = 1;
    }
    else if((kb_Data[5] & kb_6) && !pKey){
      str[index] = '6';
      index ++;
      pKey = 1;
    }
    else if((kb_Data[3] & kb_7) && !pKey){
      str[index] = '7';
      index ++;
      pKey = 1;
    }
    else if((kb_Data[4] & kb_8) && !pKey){
      str[index] = '8';
      index ++;
      pKey = 1;
    }
    else if((kb_Data[5] & kb_9) && !pKey){
      str[index] = '9';
      index ++;
      pKey = 1;
    }
    else if((kb_Data[4] & kb_DecPnt) && !pKey){
      str[index] = '.';
      index ++;
      pKey = 1;
    }
    else if((kb_Data[5] & kb_Chs) && !pKey){
      str[index] = '-';
      index ++;
      pKey = 1;
    }
    else if((kb_Data[1] & kb_Del) && !pKey){
      str[index] = ' ';
      str[index -1 ] = '_';
      index--;
      pKey = 1;
    }
    else if((kb_Data[6] & kb_Enter) && !pKey){
      str[index] = ' ';
      return 1;
    }
    else{
      pKey = 0;
    }
  }
}

void printText(char *text, uint8_t xpos, uint8_t ypos) {
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
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
  uint24_t x;
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
  uint24_t x;
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
