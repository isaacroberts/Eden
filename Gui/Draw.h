/* 
 * File:   Draw.h
 * Author: Isaac
 *
 * Created on October 3, 2013, 8:47 PM
 */

#ifndef DRAW_H
#define	DRAW_H

#include <SDL.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "Color.h"

class Draw {
public:
//Class is static
    //members
    static SDL_Renderer* render;
    static int screenWidth,screenHeight;
    static SDL_Window* window;
    static SDL_Surface* textScreen;
    static TTF_Font* font;
    static int fontSize;
    static bool drewText;
    static char* fancyFontName;
    static char* plainFontName;
    static char* curFontName;
    //other functions
    static void init();
    static SDL_Surface* makeSurface(int width,int height);
    static void end();
    static void clrScrn();
    static void preDraw();
    static void postDraw();
    
    static void resizeScreen(int width,int height);
    //color functions
    static void setColor(Color col);
    static void setColor(const Color* col);
    static void expendColor(Color* col);//sets and deletes color
    static void setColor(Color col,int alpha);
    static void setColor(Color* col,int alpha);
    static void setColor(int r,int g,int b);
    static void setColor(int r,int g,int b,int alpha);
    //drawing functions
    static void rect(SDL_Rect* rect);
    static void rect(int x1,int y1,int x2,int y2);
    static void fillScreen();
    static void fillScene();
    static void traceRect(SDL_Rect* rect);
    static void traceRect(int x1,int y1,int w,int h,int lineWidth);
    static void box(int x1,int y1,int x2,int y2,int width,int xOffset,int yOffset);
    static void traceTranslucentRect(int x1,int y1,int w,int h,int lineWidth);
    static void translucentBox(int x1,int y1,int x2,int y2,int width,int xOffset,int yOffset);
    static void line(int x1,int y1,int x2,int y2);
    static void rightLine(int x1,int y1,int x2,int y2,int width);
    static void point(int x,int y);
    
    static void traceCircle(int centerX,int centerY,int radius);
    static void circle(int centerX,int centerY,int radius);
    static void setPixel(int x,int y);
    //ttf Functions
    static void text(const char*,int x,int y);
    static void text(const char*,int x,int y,Color col);
    
    static void setFontSize(int size);
    static void useFancyFont();
    static void usePlainFont();
    static void setFont(bool fancy,int size);
   

};

#endif	/* DRAW_H */
