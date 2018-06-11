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
void draw_menu();
void draw_preview(uint8_t c1, uint8_t c2, int Iter);
/* Put all your globals here */

//C value
double cx = 0.4;
double cy = -0.1;

//Forground and background colors
uint16_t c1 = gfx_RGBTo1555(255,125,0);
uint16_t c2 = gfx_RGBTo1555(0,0,255);

//How far to render
#define xLim 160
#define yLim 240

#define ROUGH_ITER 7
#define PREVIEW_ITER 5
//Full Rendering Iterations - setable by user
int Iter = 12;

void main(void) {
    /* Fill in the body of the main function here */
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
  while (!os_GetCSC());
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
  gfx_SetColor(gfx_black);
  gfx_SetTextScale(1,1);
  gfx_PrintStringXY("A Julia set starts with a complex nu-", 67, 105);
  gfx_PrintStringXY("mber C, which is represented by the  ", 67, 115);
  gfx_PrintStringXY("crosshair in the preview. Use the ar-", 67, 125);
  gfx_PrintStringXY("row keys to change it and get differ-", 67, 135);
  gfx_PrintStringXY("ent fractals. Use the + and - keys to", 67, 145);
  gfx_PrintStringXY("change the number of iterations and ", 67, 155);
  gfx_PrintStringXY("detail level. Use the ( and ) keys to", 67, 165);
  gfx_PrintStringXY("cycle through the foreground and b-", 67, 175);
  gfx_PrintStringXY("ackground colors, respectively. Pre-", 67, 185);
  gfx_PrintStringXY("ss enter to negin rendering, and pr-", 67, 195);
  gfx_PrintStringXY("ess any key during rendering to exit.", 67, 205);

}

void draw_preview(uint8_t c1, uint8_t c2, int Iter){
  //6 x 6 blocks - resolution 54 x 40 pixels
  uint16_t x;
  uint8_t y;
  double zx;
  double zy;
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
  x = 15;
  y = 25;
  //Draw
  gfx_SetColor(gfx_black);
  gfx_HorizLine(x-3, y, 7);
  gfx_VertLine(x,y-3,7);
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
