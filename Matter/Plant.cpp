/* 
 * File:   Plant.cpp
 * Author: Isaac
 * 
 * Created on November 6, 2013, 5:33 PM
 */

#include "Plant.h"
#include "../World/Square.h"

Plant::Plant() 
{
    Plant::construct();
}
void Plant::construct() {
    Thing::construct();
    length=1;
}
Plant::~Plant() {
}
/*static*/
void Plant::updateAll()
{
}
void Plant::printInfo() const
{
    Thing::printInfo();
    cout<<"    Height= "<<length<<endl;
}
void Plant::update() 
{
    if (canGrow())
        grow(1);
    if (canReproduce())
        reproduce();
}
void Plant::changeLength(int amt)
{
    if (amt>0)
    {
        grow(amt);
    }
    else if (amt<0)
    {
        amt=-amt;
        if (length<amt)
        {
            amt=length;
        }
        loc->getLiquid()->changeMass(amt*moistureToLengthRatio());
        changeHeat(amt*heatToLengthRatio());
        length-=amt;
    }
}
void Plant::grow() {
    if (canGrow()) {
        grow(1);
    }
}
bool Plant::requisitionWater(float amt)
{
    return loc->requisitionWater(amt);
}
void Plant::grow(int amt)
{
    if (requisitionWater(amt*moistureToLengthRatio()))
    {
        loc->requireRedraw();
        length+=amt;
        changeHeat(-amt*heatToLengthRatio());
    }
}
bool Plant::canGrowOn(TerrainType* type)const {
    if (type->equals(ThingType::Dirt_T))
        return true;
    if (type->equals(ThingType::Grass_T))
        return true;
    if (type->equals(ThingType::Snow_T))
        return true;
    if (type->equals(ThingType::Roots_T))
        return true;
    else return false;
}
Color Plant::getColor()const
{
    if (burning())
        return burnColor();
    else return Color(getType()->color,heightAlpha());
}
