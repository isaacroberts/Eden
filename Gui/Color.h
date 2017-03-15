/* 
 * File:   Color.h
 * Author: Isaac
 *
 * Created on October 4, 2013, 1:09 AM
 */

#ifndef COLOR_H
#define	COLOR_H

#include <SDL.h>
#include <iostream>

using namespace std;

class Color
{
public:
    typedef unsigned char hue;
    hue red,grn,blu,alpha;
    Color(hue r,hue g,hue b)
    {
        red=r;
        grn=g;
        blu=b;
        alpha=255;
    }
    Color(hue r,hue g,hue b,hue a)
    {
        red=r;
        grn=g;
        blu=b;
        alpha=a;
    }
    Color() {
        red=grn=blu=0;
        alpha=255;
    }
    Color(const Color& orig)
    {
        red=orig.red;
        grn=orig.grn;
        blu=orig.blu;
        alpha=orig.alpha;
    }
    Color(const Color* orig,hue setAlpha)
    {
        red=orig->red;
        grn=orig->grn;
        blu=orig->blu;
        alpha=setAlpha;
    }
    Color(const Color& orig,hue setAlpha)
    {
        red=orig.red;
        grn=orig.grn;
        blu=orig.blu;
        alpha=setAlpha;
    }
    template<class num>
    Color(const Color* orig,num setAlpha)
    {
        red=orig->red;
        grn=orig->grn;
        blu=orig->blu;
        alpha=colorBound(setAlpha);
    }
    ~Color() {}
    static Color *BLACK,*WHITE,*GREY,*RED,*GREEN,*BLUE;
    static void init() 
    {
        BLACK=new Color(0,0,0);
        WHITE=new Color(255,255,255);
        GREY=new Color(125,125,125);
        RED=new Color(255,0,0);
        GREEN=new Color(0,255,0);
        BLUE=new Color(0,0,255);
    }
    static hue colorBound(double d) {
        if (d>255)
            return 255;
        else if (d<0)
            return 0;
        else return d;
    }
    static Color makeColor(double r,double g,double b)
    {
        return Color(colorBound(r),colorBound(g),colorBound(b));
    }
    static Color makeColor(double r,double g,double b,double a)
    {
        return Color(colorBound(r),colorBound(g),colorBound(b),colorBound(a));
    }
    static Color* makeNewColor(double r,double g,double b)
    {
        return new Color(colorBound(r),colorBound(g),colorBound(b));
    }
    static Color* makeNewColor(double r,double g,double b,double a)
    {
        return new Color(colorBound(r),colorBound(g),colorBound(b),colorBound(a));
    }
    void setSelf(SDL_Renderer* rend)
    {
        SDL_SetRenderDrawColor(rend,red,grn,blu,alpha);
    }
    enum AlphaMixMode {
        Add,MultiplyDifference,Avg,Greatest,Least,Opaque
    };
    static hue mixAlpha(hue a1,hue a2,double w1,double w2,AlphaMixMode mode)
    {//2 weights that may not be used
        switch (mode)
        {
            case Opaque:
                return 255;
            case Add:
                return colorBound(a1+a2);
            case MultiplyDifference:
                return 255-((255-a1)/255.*(255-a2)/255.)*255;
            case Avg:
                return ((a1*w1+a2*w2)/(w1+w2));
            case Greatest:
                return (a1>a2?a1:a2);
            case Least:
                return (a1>a2?a2:a1);
            default:
                return 255;
        }
    }
    Color avg(const Color *other,AlphaMixMode mode)
    {
        Color result=avg(other);
        result.alpha=mixAlpha(alpha,other->alpha,1,1,mode);
        return result;
    }
    Color avg(const Color *other) {
        Color result=Color(0,0,0);
        result.red=red/2 + other->red/2;
        result.grn=grn/2 + other->grn/2;
        result.blu=blu/2 + other->blu/2;
        return result;
    }
    Color avg(const Color *other,double ownWeight,AlphaMixMode mode)
    {//ownWeight must be between 1 and 0
        if (ownWeight>=1)
            return Color(*this);
        else if (ownWeight<=0)
            return Color(*other);
        return avg(other,ownWeight,1-ownWeight,mode);
    }
    Color avg(const Color *other,double ownWeight) {
        return avg(other,ownWeight,Opaque);
    }
    Color avg(const Color *other,double ownWeight,double otherWeight,AlphaMixMode mode)
    {//weight is between 1 and 0
        //adds alpha, avgs everything else
        Color result=Color(0,0,0);
        result.red=(red*ownWeight + other->red*otherWeight)/(ownWeight+otherWeight);
        result.grn=(grn*ownWeight + other->grn*otherWeight)/(ownWeight+otherWeight);
        result.blu=(blu*ownWeight + other->blu*otherWeight)/(ownWeight+otherWeight);
        result.alpha=mixAlpha(alpha,other->alpha,ownWeight,otherWeight,mode);
        return result;
    }
    Color avg(const Color *other,double ownWeight,double otherWeight) {
        return avg(other,ownWeight,otherWeight,Opaque);
    }
private:
    
};

#endif	/* COLOR_H */

