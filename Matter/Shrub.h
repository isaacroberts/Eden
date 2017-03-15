/* 
 * File:   Shrub.h
 * Author: Isaac
 *
 * Created on November 6, 2013, 9:07 PM
 */

#ifndef SHRUB_H
#define	SHRUB_H

#include "Plant.h"
#include "../World/Square.h"

class Shrub : public Plant
{
public:
    Shrub() :  Plant() 
    {
//        Plant::construct();
    }
    Shrub* clone() const {
        Shrub* copy=new Shrub();
        copy->makePropertiesSameAs(this);
        copy->length=length;
        return copy;
    }
    ThingType* getType()const {
        return ThingType::Shrub_T;
    }
    virtual ~Shrub() {}
    sizeval getSize()const{return SizeVal::Medium;}
    float height() const{
        return length/100.0;
    }
    float surfaceArea()const {
        return  1.4;//found by combining wild guesses with
                        //careful mathematical processes
    }    
    float sideSurfaceArea() const {
        return length/200.0;// height/2 (probably)
    }
    virtual float heatToLengthRatio()
    {
        return 1;
    }
    virtual float moistureToLengthRatio()
    {
        return .1;
    }
    virtual int heightAlpha()const {
        return Color::colorBound(length*10+10);
    }
    virtual Color burnColor() const{
        return Color(255,100,0);
    }
    void grow(int amt) {
        if (requisitionWater(amt*moistureToLengthRatio()))
        {
            length+=amt;
            heat-=amt*heatToLengthRatio();
        }
        else if (length<3 && length>0)
        {
            changeLength(-1);
        }
    }
    bool reproduce() 
    {
        if (canReproduce())
        {
            if (requisitionWater(3))
            {
                Square* growTo=loc;
                for (int n=0;n<5;++n)
                    growTo=growTo->transform(Dir::getRandDir());
                if (growTo->notError())
                {
                    if (canGrowOn(growTo->getTerrain()->getType()))
                    {
                        if (!growTo->hasOccOfType(ThingType::Shrub_T))
                        {
                            growTo->addOccupant(new Shrub());
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
protected:
    void calcHeat() 
    {
        if (underwater())
            heat=loc->getLiquid()->getHeat();
        else
            heat=loc->getSky()->getHeat();
    }
    void burn() {
        changeLength(-1);
        heat+=2;
    }
public:
    bool canGrowOn(TerrainType* type) {
        if (type->equals(ThingType::Sand_T))
            return true;
        else return false;
    }
    bool canGrow()const {
        if ( length<=12)
            return Util::everyNth(125);
        else return false;
    }
    bool canReproduce()const {
        if (length>=6)
            return Util::everyNth(5);
        else return false;
    }
};

#endif	/* SHRUB_H */

