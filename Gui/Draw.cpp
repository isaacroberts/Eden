/* 
 * File:   Draw.cpp
 * Author: Isaac
 * 
 * Created on October 3, 2013, 8:47 PM
 */

#include <SDL/SDL.h>

#include <SDL/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include "Draw.h"
#include "Util.h"
#include "../main.h"
#include "../World/Square.h"
#include "Event.h"
#include "Gui.h"

SDL_Renderer* Draw::render;
SDL_Window* Draw::window;
SDL_Surface* Draw::textScreen;
TTF_Font* Draw::font;
int Draw::screenWidth;
int Draw::screenHeight;
int Draw::fontSize;//used to make sure Draw isnt needlessly
        //closing and reopening a Font of the same size
bool Draw::drewText;
char* Draw::fancyFontName="Fonts/BlackChancery.ttf";
char* Draw::plainFontName="Fonts/Antigrav.ttf";
char* Draw::curFontName=Draw::fancyFontName;
void Draw::init()
{
    screenWidth=1500;
    screenHeight=1000;
    SDL_Init(SDL_INIT_TIMER);
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window=SDL_CreateWindow("main",10,10,screenWidth,screenHeight,
            SDL_WINDOW_RESIZABLE);//|SDL_WINDOW_FULLSCREEN_DESKTOP);
//    textScreen=SDL_CreateRGBSurface(0,screenWidth,screenHeight,32,0xff,0xff00,0xff0000,0xff000000);
    
    textScreen=makeSurface(screenWidth,screenHeight);
    render=SDL_CreateRenderer(window,-1,0);
    font=TTF_OpenFont(fancyFontName,15);
    if (font==NULL)
    {
        cout<<" Font "<<fancyFontName<<" not found.\n";
        cout<<"   Exiting.\n";
        exit(0);
    }
    fontSize=15;
    SDL_SetRenderDrawBlendMode(render,SDL_BLENDMODE_BLEND);
    drewText=true;
//    SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
}
SDL_Surface* Draw::makeSurface(int width, int height)
{
    SDL_Surface* surf;
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        surf = SDL_CreateRGBSurface(0,width,height,32, 0xFF000000, 0xFF0000,0xFF00, 0xFF);
    else
        surf = SDL_CreateRGBSurface(0,width,height,32, 0xFF, 0xFF00, 0xFF0000, 0xFF000000);
    SDL_UnlockSurface(surf);
    SDL_SetSurfaceBlendMode(surf,SDL_BLENDMODE_BLEND);
    return surf;
}
void Draw::end()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    TTF_Quit();
    SDL_Quit();
}

void Draw::resizeScreen(int width, int height)
{
    screenWidth=width;
    screenHeight=height;
    cout<<"resized to "<<screenWidth<<" x "<<screenHeight<<endl;
    Gui::setGridScreenSize(Gui::minPx,Gui::minPy,screenWidth-40,screenHeight-100);
    SDL_FreeSurface(textScreen);
    textScreen=makeSurface(screenWidth,screenHeight);
    Gui::globalRedraw=3;
    Event::guiRedraw=3;
}
void Draw::clrScrn()
{
    SDL_SetRenderDrawColor(render,0,0,0,255);
    
    SDL_RenderClear(render);
    SDL_Rect rect={0,0,screenWidth,screenHeight};
    SDL_FillRect(textScreen,&rect,0);    
}
void Draw::preDraw()
{
    SDL_SetRenderDrawColor(render,0,0,0,255);
    if (Event::guiRedraw)
    {
        if (Gui::needsGlobalRedraw())
        {
            fillScreen(); 
        }
        else
        {
            int xEdge=Gui::maxPx+Square::squareSize;
            int yEdge=Gui::maxPy+Square::squareSize;
            SDL_Rect rect={0,0,Gui::minPx,screenHeight};
            SDL_RenderFillRect(render,&rect);
            rect=(SDL_Rect){Gui::minPx,0,
                    screenWidth-Gui::minPx,Gui::minPy};
            SDL_RenderFillRect(render,&rect);
            rect=(SDL_Rect){xEdge,Gui::minPy,
                    screenWidth-xEdge,screenHeight-Gui::minPy};
            SDL_RenderFillRect(render,&rect);
            rect=(SDL_Rect){Gui::minPx,yEdge,
                    screenWidth-Gui::minPx,screenHeight-yEdge};
            SDL_RenderFillRect(render,&rect);
        }
    }
    else if (Gui::needsGlobalRedraw())
    {
        SDL_Rect rect={Gui::minPx,Gui::minPy,Gui::maxPx,Gui::maxPy};
        SDL_FillRect(textScreen,&rect,0);
    }
//    if (drewText)
    {
        SDL_Rect rect={0,0,screenWidth,screenHeight};
        SDL_FillRect(textScreen,&rect,0);
        drewText=false;
    }
}
void Draw::postDraw()
{
//        long time=SDL_GetTicks();
    if (drewText)
    {
        SDL_Texture* texture=SDL_CreateTextureFromSurface(render,textScreen);
        SDL_RenderCopy(render,texture,NULL,NULL);
        SDL_DestroyTexture(texture);
    }
//        time=SDL_GetTicks()-time;
    SDL_RenderPresent(render);
//        printf("    postDraw time=%3ld",time);
}
//color functions
void Draw::setColor(Color col)
{
    SDL_SetRenderDrawColor(render,col.red,col.grn,col.blu,col.alpha);
}
void Draw::setColor(const Color* col)
{
    SDL_SetRenderDrawColor(render,col->red,col->grn,col->blu,col->alpha);
}
void Draw::expendColor(Color* col)
{//sets and deletes it for instances of single-use created colors
    SDL_SetRenderDrawColor(render,col->red,col->grn,col->blu,col->alpha);
    delete col;
}
void Draw::setColor(Color col, int alpha) {
    SDL_SetRenderDrawColor(render,col.red,col.grn,col.blu,alpha);
}
void Draw::setColor(Color* col, int alpha) {
    SDL_SetRenderDrawColor(render,col->red,col->grn,col->blu,alpha);
}
void Draw::setColor(int r, int g, int b)
{
    SDL_SetRenderDrawColor(render,r,g,b,255);
}
void Draw::setColor(int r, int g, int b,int alpha)
{
    SDL_SetRenderDrawColor(render,r,g,b,alpha);
}
//drawing functions
void Draw::rect(SDL_Rect* rect)
{
    SDL_RenderFillRect(render,rect);
}
void Draw::rect(int left, int top, int right, int bottom)
{
    SDL_Rect rect={left,top,right,bottom};
    SDL_RenderFillRect(render,&rect);
}
void Draw::traceRect(SDL_Rect* rect)
{
    SDL_RenderDrawRect(render,rect);
}
void Draw::traceTranslucentRect(int left, int top, int width, int length,int lineWidth)
{//uses width & length
    int overlap=lineWidth/2;
    int bottom=top+length;
    int right=left+width;
    rightLine(left,top,left,bottom-overlap,lineWidth);
    rightLine(left,bottom,right-overlap,bottom,lineWidth);
    rightLine(right,bottom,right,top+overlap,lineWidth);
    rightLine(right,top,left+overlap,top,lineWidth);
}

void Draw::translucentBox(int left, int top, int right, int bottom,
                int width,int xOffset,int yOffset)
{//rect from pt1 to pt2. left/right and top/bottom do not need to be sorted.
    if (top>bottom)
        Util::swap(&top,&bottom);
    if (left>right)
        Util::swap(&right,&left);
    right+=xOffset;
    bottom+=yOffset;
    int overlap=width/2;
    rightLine(left,top,left,bottom-overlap,width);
    rightLine(left,bottom,right-overlap,bottom,width);
    rightLine(right,bottom,right,top+overlap,width);
    rightLine(right,top,left+overlap,top,width);
}
void Draw::traceRect(int left, int top, int width, int length,int lineWidth)
{//uses width & length
    int bottom=top+length;
    int right=left+width;
    rightLine(left,top,left,bottom,lineWidth);
    rightLine(left,bottom,right,bottom,lineWidth);
    rightLine(right,bottom,right,top,lineWidth);
    rightLine(right,top,left,top,lineWidth);
}
void Draw::box(int left, int top, int right, int bottom,
                int width,int xOffset,int yOffset)
{//rect from pt1 to pt2. left/right and top/bottom do not need to be sorted.
    if (top>bottom)
        Util::swap(&top,&bottom);
    if (left>right)
        Util::swap(&right,&left);
    right+=xOffset;
    bottom+=yOffset;
    rightLine(left,top,left,bottom,width);
    rightLine(left,bottom,right,bottom,width);
    rightLine(right,bottom,right,top,width);
    rightLine(right,top,left,top,width);
}
void Draw::fillScreen()
{
    SDL_Rect rect={0,0,screenWidth,screenHeight};
    SDL_RenderFillRect(render,&rect);
}
void Draw::fillScene()
{
    SDL_Rect rect={Gui::minPx,Gui::minPy,
    Gui::maxPx-Gui::minPx,Gui::maxPy-Gui::minPy};
    SDL_RenderFillRect(render,&rect);
}
void Draw::circle(int cx, int cy, int radius)
{
    if (radius<=2)
    {
        for (int x=-radius;x<=radius;x++)
        {
            for (int y=-radius;y<=radius;y++)
            {
                if (abs(x)+abs(y)<=radius)
                    setPixel(cx+x,cy+y);
            }
        }
        return;
    }
    //this is a modified bresenham circle algorithm
    //instead of painting the eight edges, it paints every point from 
    // px=0 to px=x on each y
    //it has to avoid overlap in case the color is translucent
    int x=radius,y=1;
    int slopeTracker=1-radius;
    double internalSquareRad;
    internalSquareRad=(radius)/1.41421356   +.25;
    //the radius of a square touching a circle on all four points is r/√2
    //the overlap of the fill-modified bresenham algorithm is a cocentric square in the center
    //to avoid the overlap, dont color the reflection inside of this square
    while (x>=y)
    {
        for (int fillX=1;fillX<=x;fillX++)
        {
            setPixel(cx+fillX,cy+y);
            setPixel(cx+fillX,cy-y);
            setPixel(cx-fillX,cy+y);
            setPixel(cx-fillX,cy-y);
            //reflect along y=x 
            if (fillX>internalSquareRad)
            {//avoid overlap
                setPixel(cx+y,cy+fillX);
                setPixel(cx-y,cy+fillX);
                setPixel(cx+y,cy-fillX);
                setPixel(cx-y,cy-fillX);
            }
        }
        
        
        ++y;
        if (slopeTracker<0)
           slopeTracker+=2*y +1;
        else
        {
            --x;
            //devil magic involving derivatives
            slopeTracker+=2*(y-x+1);
        }
    }
    for (int y=1;y<=radius;++y)
    {//previous loop skips center lines to avoid overlap
        setPixel(cx+y,cy);
        setPixel(cx,cy+y);
        setPixel(cx-y,cy);
        setPixel(cx,cy-y);
    }
    //center-line-loop skips center to avoid overlap
    setPixel(cx,cy);
}
void Draw::traceCircle(int cx, int cy, int radius)
{
    int x=radius,y=0;
    int slopeTracker=1-radius;
    while (x>=y)
    {
        //draw four side octants
        setPixel(cx+x,cy+y);
        setPixel(cx-x,cy+y);
        setPixel(cx+x,cy-y);
        setPixel(cx-x,cy-y);
        //draw flip of x & y because circle is symmetrical
        //reflects over y=x and y=-x line
        //draws top and bottom four octants
        setPixel(cx+y,cy+x);
        setPixel(cx-y,cy+x);
        setPixel(cx+y,cy-x);
        setPixel(cx-y,cy-x);
        
        ++y;
        if (slopeTracker<0)
           slopeTracker+=2*y +1;
        else
        {
            --x;
            //devil magic involving derivatives
            slopeTracker+=2*(y-x+1);
        }
    }
}
void Draw::setPixel(int x, int y)
{
    SDL_RenderDrawPoint(render,x,y);
}
void Draw::line(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(render,x1,y1,x2,y2);
}
void Draw::rightLine(int x1, int y1, int x2, int y2,int width)
{
    if (!(x1==x2 || y1==y2))
    {
        cout<<"Called rightLine on a non-right line"<<endl;
        cout<<"rightLines are at 90 degree angles."<<endl;
        if (x1==x2)
            cout<<"     Ys do not match."<<endl;
        else cout<<"      Xs do not match."<<endl;
        return;
    }
    if (x1>x2) {
        Util::swap(&x1,&x2);
    }
    if (y1>y2) {
        Util::swap(&y1,&y2);
    }
    int offset=width>>1; // = width/2
    SDL_Rect line={x1-offset,y1-offset,x2-x1+offset,y2-y1+offset};
    SDL_RenderFillRect(render,&line);
}
void Draw::point(int x, int y)
{
    SDL_RenderDrawPoint(render,x,y);
}
//text drawing
void Draw::setFont(bool fancy, int size)
{
    char* name=(fancy?fancyFontName:plainFontName);
    if (name!=curFontName || fontSize!=size)
    {
        curFontName=name;
        fontSize=size;
        TTF_CloseFont(font);
        font=TTF_OpenFont(curFontName,size);
    }
}
void Draw::setFontSize(int size)
{
    if (fontSize!=size)
    {
        fontSize=size;
        TTF_CloseFont(font);
        font=TTF_OpenFont(curFontName,size);
    }
}
void Draw::useFancyFont()
{
    if (curFontName!=fancyFontName)
    {
        curFontName=fancyFontName;
        TTF_CloseFont(font);
        font=TTF_OpenFont(curFontName,fontSize);
    }
}
void Draw::usePlainFont()
{
    if (curFontName!=plainFontName)
    {
        curFontName=plainFontName;
        TTF_CloseFont(font);
        font=TTF_OpenFont(curFontName,fontSize);
    }
}
void Draw::text(const char* str, int x, int y,Color col)
{
    drewText=true;
    SDL_Color color=(SDL_Color){col.red,col.grn,col.blu,col.alpha};
    SDL_Surface *text=TTF_RenderText_Solid(font,str,color);
    SDL_Rect copyTo={x,y,1200-x,1000-y};
    SDL_BlitSurface(text,NULL,textScreen,&copyTo);
    SDL_FreeSurface(text);
}
void Draw::text(const char* str, int x, int y)
{
    drewText=true;
    SDL_Color col;
    SDL_GetRenderDrawColor(render,&col.r,&col.g,&col.b,&col.a);
    SDL_Surface *text=TTF_RenderText_Solid(font,str,col);
    SDL_Rect copyTo={x,y,1200-x,1000-y};
    SDL_BlitSurface(text,NULL,textScreen,&copyTo);
    SDL_FreeSurface(text);
}




//defining Color symbols here so that I don't have to 
//have a separate .cpp file for Color just for these
Color *Color::BLACK,*Color::WHITE,*Color::GREY;
Color *Color::RED,*Color::GREEN,*Color::BLUE;