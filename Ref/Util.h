/* 
 * File:   Util.h
 * Author: Isaac
 *
 * Created on October 5, 2013, 10:40 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#include <math.h>
//#include <vector>
#include <SDL.h>
#include <utility>

#include "GlobalInclude.h"

class Square;

typedef long kilogram;
typedef long joule;



namespace Util
{
    /*---------Time-------------------*/
    extern long frames;
    inline long time() {return frames;}
    inline void update() {frames++;}
    inline bool everyNth(long freq,long offset) {
        return (frames+offset)%freq==0;
    }
    inline bool everyNth(long freq) {
        return frames%freq==0;
    }
    /*-------------Number operators------------*/
    //calculations
    double roughSinOfArcTan(double slope);//gives you the force ratio given the slope
        //random
    inline double randDouble() {
        return (double)(rand()%1000)/1000.;
    }
    inline double randDouble(double range) {
        return (double)(rand()%1000)*range/1000;
    }
    inline double randDouble(int divideBy) {
        return (double)(rand()%1000)/(double)divideBy;
    }
        //basic computer-ish things
    inline int roundUp(double d)
    {
        if ((int)d<d)
            d++;
        return (int)d;
    }
    inline void swap(int* x1,int* x2) {
        int temp=*x1;
        *x1=*x2;
        *x2=temp;
    }
    int binaryModulus(int a,int power);
    bool greaterMagn(double a,double b);
    bool equalMagn(double a,double b);
    void reduceMagn(double& reduce,double amt);
    //Checks
    bool bad(float f);
    bool bad(double d);
    template <class Num>
    inline void ensurePositive(Num& x) {
        if (x<0)
            x=0;
    }
        //comparisons 
    template <class Num,class SecNum>
    inline void ensureAbove(Num& number,const SecNum min) {
        if (number<min)
            number=min;
    }
    template <class Num,class SecNum>
    inline void ensureBelow(Num& number,const SecNum max) {
        if (number>max)
            number=max;
    }
    template<class Num,class SecNum,class ThirdNum>
    void trickle(Num& trickleFrom,SecNum& trickleTo,ThirdNum trickleRate)
    {
        if (trickleRate>0)
        {
            
            trickleFrom-=trickleRate;
            trickleTo+=trickleRate;
            if (trickleFrom<0)
            {
                trickleTo+=trickleFrom;
                if (trickleTo<0)
                    trickleTo=0;
                trickleFrom=0;
            }
        }
        else
        {
            trickle(trickleTo,trickleFrom,trickleRate);
        }
    }
    inline bool floatEqual(float f1,float f2) {
        float dif=f1-f2;
        if (dif>.001)
            return false;
        if (dif<-.001)
            return false;
        return true;
    }
    inline bool floatEqual(double f1,double f2) {
        double dif=f1-f2;
        if (dif>.001)
            return false;
        if (dif<-.001)
            return false;
        return true;
    }
    inline double max(double d1,double d2) { return (d1>d2?d1:d2); }
        //basic arithmatic
    double weightedDif(double val1,double weight1,double val2,double weight2);
    double avg(double val1,double weight1,double val2,double weight2);
    inline double avg(double val1,double val2)
    {
        return (val1+val2)/2;
    }
    /*------------geographic operators---------------*/
        //distance
    int xDist(int,int);
    int xVectorComponent(int,int);
    inline double sqrdDist(int x1, int y1, int x2, int y2)
    {
        return pow(xDist(x1,x2),2)+pow(y1-y2,2);
    }
    double dist(Square* pos1, Square* pos2);
    inline double dist(int x1, int y1, int x2, int y2)
    {
        return sqrt(sqrdDist(x1,y1,x2,y2));
    }
    double sqrdDist(Square* pos1, Square* pos2);
    double gridDist(Square* pos1,Square* pos2);
    double changeInDist(int x,int y,int dx,int dy);
        //rectangles
    SDL_Rect makeRect(int x1,int y1,int x2,int y2);
    SDL_Rect makeScreenRect(Square*,Square*);
    SDL_Rect makeScreenPixelRect(Square*,Square*);
    bool onScene(int px,int py);
    bool contains(SDL_Rect* rect,int x,int y);
    bool contains(int rectX,int rectY,int rectW,int rectH,int pointX,int pointY);
    bool roughlyInCircle(int circleX,int circleY,int circleRadius,int pointX,int pointY);
            //checks if point is in rectangle around circle
    std::pair<double,int> getChainingGenerationParameters(int size);
    
}
//more common functions that should be outside
//of the Util namespace to make code more readable
typedef unsigned char byte;
extern int mod (int a,int b);
extern double abs(const double d);
extern bool freq(int current,int total,int desiredAmountOfHits);

//geographic
typedef int coord;
const int COORD_RESOLUTION=256;
int moveCoord(coord& coordinate,int deltaCoord);//returns squares moved and changes coord& ref
    
 

#endif	/* UTIL_H */

