/* 
 * File:   Util.cpp
 * Author: Isaac
 * 
 * Created on October 3, 2013, 8:10 PM
 */

#include "Util.h"
#include "../main.h"
#include "Dir.h"
#include "../Gui/Gui.h"

double errorDoubleRef=-1;

namespace Util
{
    long frames=0;
    bool bad(float num)
    {
        if (isnan(num))
            return true;
        if (num==std::numeric_limits<float>::infinity())
            return true;
        return false;
    }
    bool bad(double num)
    {
        if (isnan(num))
            return true;
        if (num==std::numeric_limits<double>::infinity())
            return true;
        return false;
    }
    int binaryModulus(int a,int power)
    {
        int mask=0;
        for (int p=0;p<power;p++)
        {
            mask+=1<<p;
        }
        return a&mask;;
    }
//    template <class Num,class SecNum>
//    bool greaterMagn(Num a, SecNum b)
    bool greaterMagn(double a,double b)
    {
        bool aPos=a>0;
        bool bPos=b>0;
        if (aPos^bPos)
            b=-b;
        if (aPos)
            return a>b;
        else 
            return a<b;
    }
//    template <class Num,class SecNum>
//    bool equalMagn(Num a, SecNum b)
    bool equalMagn(double a,double b)
    {
        if ((a>0)^(b>0))
            b=-b;
        return a==b;
    }
    void reduceMagn(double& reduce,double amt)
    {
        if (reduce>0)
        {
            reduce-=amt;
            if (reduce<0)
                reduce=0;
        }
        else
        {
            reduce+=amt;
            if (reduce>0)
                reduce=0;
        }
    }
    double weightedDif(double val1,double weight1, double val2, double weight2)
    {
        if (weight1<=0)
        {
            if (weight2<=0)
                return 0;
            else
                return val2;
        }
        else if (weight2<=0)
            return val1;
        double dif=val1*weight1 - val2*weight2;
        dif/=weight1+weight2;
        dif/=2.0;
        return dif;
    }
    double avg(double val1, double weight1, double val2, double weight2)
    {
        if (weight1<=0)
        {
            if (weight2<=0)
                return 0;
            else
                return val2;
        }
        else if (weight2<=0)
            return val1;
        
        double mean=val1*weight1 + val2*weight2;
        mean/=weight1+weight2;
        return mean;
    }
    //calculations
    double roughSinOfArcTan(double slope)
    {//        f(x)=sin(arctan(x))
        double absSlope=abs(slope);
        if (absSlope<=.4)//for |x|<.4
            return slope;//  f(x)=x
        else if (absSlope>2) // for |x|>2
        {                    //  f(x)=±1
            if (slope>0)
                return 1;
            else return -1;
        }
        else if (absSlope<=1) //for .4<|x|<1
        {                     //  f(x)=x/2 ±.2 
            return slope/2 +(slope>0?.2:-.2);
        }
        else // for 1<|x|<2
        {    //  f(x)=x/5 ± .52
            return slope/5 + (slope>0?.52:-.52);
        }
    }
    //geographic functions
    int xDist(int x1, int x2)
    {
        int dist=abs(x1-x2);
        if (Earth::wraparound)
        {
            int wrapDist=GRID.xAmt-dist;
            if (wrapDist<dist)
                return wrapDist;
            else return dist;
        }
        else
            return dist;
    }
    int xVectorComponent(int x1,int x2)
    {
        if (Earth::wraparound)
        {
            int dist=x2-x1;
            int wrapDist=GRID.xAmt-abs(dist);
            if (wrapDist<abs(dist))
            {
                if (x1<x2)
                    return -wrapDist;
                else return wrapDist;
            }
            else return dist;
        }
        else return x2-x1;
    }
    double dist(Square* pos1, Square* pos2)
    {
        return sqrt(  pow(xDist(pos1->x(),pos2->x()),2)
                +pow(pos1->y()-pos2->y(),2)   );
    }
    double sqrdDist(Square* pos1, Square* pos2)
    {
        return pow(xDist(pos1->x(),pos2->x()),2)
                +pow(pos1->y()-pos2->y(),2);
    }
    double gridDist(Square* pos1, Square* pos2)
    {
        return xDist(pos1->x(),pos2->x()) + abs(pos1->y()-pos2->y());
    }
    double changeInDist(int x, int y, int dx, int dy)
    {
        if (dx<0 && x<=0)
            dx=-dx;
        else if (x<0 && dx>0)
            dx=-dx;
        if (dy<0 && y<=0)
            dy=-dy;
        else if (y<0 && dy>0)
            dy=-dy;
        float fx=x,fy=y;
        double deltaDist=0;
        if (dx!=0)
        {
            if (y==0)
                deltaDist=dx;
            else if (abs(x)>abs(fy)*2)
            {
                deltaDist=dx;
            }
            else if (abs(x)<abs(fy)/2)
            {
                deltaDist=dx * abs(fx/fy);
            }
            else
            {
                deltaDist=dx * sqrt(abs(fx/fy))/1.5;
            }
        }
        if (dy!=0)
        {
            if (x==0)
                deltaDist+=dy;
            else if (abs(y)>abs(fx)*2)
            {
                deltaDist+=dy;
            }
            else if (abs(y)<abs(fx)/2)
            {
                deltaDist+=dy * abs(fy/fx);
            }
            else
            {
                deltaDist+=dy * sqrt(abs(fy/fx))/1.5;
            }
        }
        return deltaDist;
    }
    SDL_Rect makeRect(int x1,int y1,int x2,int y2)
    {  //make a rectangle thats (lowest point, highest point)
        if (x2<x1)
        {
            int temp=x1;
            x1=x2;
            x2=temp;
        }
        if (y2<y1)
        {
            int temp=y1;
            y1=y2;
            y2=temp;
        }
        SDL_Rect rect=(SDL_Rect){x1,y1,x2,y2};
        return rect;
    }
    SDL_Rect makeScreenRect(Square* s1,Square* s2)
    {  //make a rectangle thats (first point,second point)
//        if (!Earth::wraparound)
            return makeRect(s1->x(),s1->y(),s2->x(),s2->y());
        int y1=s1->y();
        int y2=s2->y();
        if (y2<y1)
        {
            int temp=y1;
            y1=y2;
            y2=temp;
        }
        int px1=mod(s1->px(),GRID.pixWidth());
        int px2=mod(s2->px(),GRID.pixWidth());
        if (px1>px2)
        {
            int temp=px2;
            px2=px1;
            px1=temp;
        }
        int x1=GRID.getSquareByPixel(px1,s1->py())->x();
        int x2=GRID.getSquareByPixel(px2,s2->py())->x();
        SDL_Rect rect=(SDL_Rect){x1,y1,x2,y2};
        return rect;
    }
    SDL_Rect makeScreenPixelRect(Square* s1,Square* s2)
    {  //make a rectangle thats (first point,second point)
        int py1=s1->py();
        int py2=s2->py();
        if (py2<py1)
        {
            int temp=py1;
            py1=py2;
            py2=temp;
        }
        int px1=mod(s1->px(),GRID.pixWidth());
        int px2=mod(s2->px(),GRID.pixWidth());
        if (px1>px2)
        {
            int temp=px2;
            px2=px1;
            px1=temp;
        }
        SDL_Rect rect=(SDL_Rect){px1,py1,px2-px1+Square::squareSize,py2-py1+Square::squareSize};
        return rect;
    }
    pair<double,int> getChainingGenerationParameters(int size)
    {
        pair<double,int> param;
        if (size>=GRID.amt()*.75)
        {
            param.second=10;
            param.first=pow(size-GRID.amt()*.75,2)*3e-5+.3;
        }
        if (size>=2000)
        {
            param.second=4;
            param.first=sqrt(size)*2.3e-3 -1.2e-2;
        }
        else if (size>=200)
        {
            param.second=4;
            param.first=sqrt(size)*2.2e-3 - 6e-3;
        }
        else if (size<100)
        {
            param.first=0;
            param.second=Util::roundUp(sqrt(size)/3.14);
        }
        else
        {
            param.second=4;
            param.first=size*1.7e-4 - 8e-3;
        }
        return param;
    }
    bool onScene(int x,int y)
    {
        if (x<Gui::minPx)
            return false;
        if (y<Gui::minPy)
            return false;
        if (x>Gui::maxPx)
            return false;
        if (y>Gui::maxPy)
            return false;
        return true;
    }
    bool contains(SDL_Rect* rect,int x,int y)
    {
        if (x<rect->x)
            return false;
        if (y<rect->y)
            return false;
        if (x>rect->x+rect->w)
            return false;
        if (y>rect->y+rect->h)
            return false;
        return true;
    }
    bool contains(int rx, int ry, int rw, int rh, int px, int py)
    {
        if (px<rx)
            return false;
        if (py<ry)
            return false;
        if (px>rx+rw)
            return false;
        if (py>ry+rh)
            return false;
        return true;
    }
    bool roughlyInCircle(int cx,int cy,int rad,int px,int py)
    {//checks if point is in rectangle around circle
        if (px<cx-rad)
            return false;
        if (py<cy-rad)
            return false;
        if (px>cx+rad)
            return false;
        if (py>cy+rad)
            return false;
        return true;
    }
}
extern int mod (int a,int b) 
{//a god-fearing modulus function that doesnt return negative values
    if (b==0)
    {
        cout<<"ISECFAULT: mod("<<a<<",0);"<<endl;
        exit(2);
    }
    if (a>0)
    {
        if (b==2)
            return a&1;
        while (a>=b)
            a-=b;
        return a;
    }
    else if (a<0)
    {
        if (b==2)
            return (-a)&1;
        while (a<0)
            a+=b;
        return a;
    }
    else return 0;
}
extern double abs(const double d)
{
    if (d<0)
        return -d;
    else return d;
}
extern bool freq(int current,int total,int amtHits)
{
    if (total<amtHits)
        return false;
    return (current%(total/amtHits)==0);
}
int moveCoord(coord& coordinate, int deltaCoord)
{
    int squareMovement=0;
    deltaCoord+=coordinate;
    while (deltaCoord>COORD_RESOLUTION)
    {
        squareMovement++;
        deltaCoord-=COORD_RESOLUTION;
    }
    while (deltaCoord<0)
    {
        squareMovement--;
        deltaCoord+=COORD_RESOLUTION;
    }
    coordinate=deltaCoord;
    return squareMovement;
}