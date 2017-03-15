/* 
 * File:   Blood.h
 * Author: Isaac
 *
 * Created on November 20, 2013, 3:22 PM
 */

#ifndef BLOOD_H
#define	BLOOD_H

#include "Liquid.h"

class Blood : public Liquid
{
    public:
    Blood() : Liquid()
    {
//        heat=310;
    }
    LiquidType* getLiquidType()const{
        return LiquidType::Blood_T;
    }
    Blood* clone()const
    {
        Blood* copy=new Blood();
        copy->setHeat(heat);
        copy->setLoc(loc);
        copy->saturatedMass=saturatedMass;
        copy->mass=mass;
        copy->setDeltaDroplets(deltaMass);
        return copy;
    }
    Color::hue colorAlpha()const
    {
        if (mass>5)
            return Color::colorBound(mass*.15+50);
        else if (getSaturation()>0 && saturatedMass>0)
            return Color::colorBound((saturatedMass/getSaturation())*50.0);
        else return 0;
    }
};

#endif	/* BLOOD_H */

