/* 
 * File:   Water.cpp
 * Author: Isaac
 * 
 * Created on October 11, 2013, 11:54 AM
 */

//#include <vector>
#include "Water.h"
#include "../World/Square.h"

using namespace std;

Water::Water() : Liquid()
{
}
Water* Water::clone() const
{
    Water* copy=new Water();
    copy->setLoc(loc);
    copy->saturatedMass=saturatedMass;
    copy->mass=mass;
    copy->setHeat(heat);
    copy->setDeltaDroplets(deltaMass);
    return copy;
}
Water::~Water() 
{
}
void Water::update()
{
    Liquid::update();
    evaporate();
}
void Water::evaporate()
{
    double evap=Earth::getEvaporation(heat,
            mass,1,loc->getSky()->getHumidity()  );
    changeMass(-evap);
    changeHeat(-evap*getSpecHeat());
    loc->getSky()->changeHumidity(evap);
}
/*static*/ float Water::getErosion(float moistureFlow, Terrain* from)
{
    return moistureFlow/100000000.0 * from->getType()->erosionRate;
}
//setters

//accessors
Color::hue Water::colorAlpha() const
{
    if (mass>0)
        return Color::colorBound((mass)*.25);
    return 0;
}