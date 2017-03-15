/* 
 * File:   Lava.cpp
 * Author: Isaac
 * 
 * Created on November 15, 2013, 1:03 PM
 */

#include "Lava.h"
#include "../World/Square.h"

Lava::Lava() : Liquid() 
{
//    heat=1200;
}
Lava* Lava::clone() const
{
    Lava* copy=new Lava();
    copy->setLoc(loc);
    copy->setHeat(heat);
    copy->saturatedMass=saturatedMass;
    copy->mass=mass;
    copy->setDeltaDroplets(deltaMass);
    return copy;
}
void Lava::update()
{
    Liquid::update();
    if (heat<freezePoint())
    {
        float rockFreeze=(freezePoint()-heat)/10;
        if (mainLiquidMass()<rockFreeze)
            rockFreeze=mainLiquidMass();
        addAndSatMass(-rockFreeze);
        loc->getTerrain()->addLandMass(rockFreeze);
    }
}
Color::hue Lava::colorAlpha() const
{
    if (submerged())
        return Color::colorBound(mass*.06);
    else return 0;
}
Lava::~Lava() {
}

