/* 
 * File:   Grass.cpp
 * Author: Isaac
 * 
 * Created on October 5, 2013, 2:18 PM
 */

#include "Grass.h"
#include "Dirt.h"
#include "Covering.h"
#include "../World/Square.h"

const int Grass::GROWTH_FREQ=8;
const int Grass::REPRODUCE_FREQ=18;
Grass::Grass() : Terrain()
{
    construct();
}
void Grass::construct()
{
    Terrain::construct();
    length=1;
}
Grass* Grass::clone() const
{
    Grass *g=new Grass();
    g->makePropertiesSameAs(this);
    g->length=length;
    return g;
}
Grass::~Grass() 
{
//    loc->getAir()->changeHumidity(height*moistureToHeightRatio);
//    loc->getAir()->changeHeat(height*heatToHeightRatio);
}
//doers
void Grass::update()
{
    if (underwater())
    {
        if (Util::everyNth(21))
            changeLength(-1);
    }
    else 
    {
        if (canGrow())
            grow(1);
        if (canReproduce())
            reproduce();
    }
}
bool Grass::canGrow() const{
    if (underwater())
        return false;
    else if (length<150)
        return Util::everyNth(GROWTH_FREQ,loc->getHash());
    else return false;
}
bool Grass::canReproduce() const{
    //if (Util::everyNth(REPRODUCE_FREQ,loc->getHash()))
    return length>=20 && loc->notError();
    //else return false;
}
void Grass::burn()
{
    if (heat<getFlashPoint()+50)
        loc->requireRedraw();
    changeLength(-2);
    heat++;
}
//setters
float Grass::heatToLengthRatio() {
    return 0.05;
}
float Grass::moistureToLengthRatio() {
    return .75;
}
void Grass::grow(int amt)
{
    if (requisitionWater(amt*moistureToLengthRatio()))
    {
        length+=amt;
        if (length < 140 && length%5==0)
            loc->requireRedraw();
        changeHeat(-amt*heatToLengthRatio());
    }
}
void Grass::grow()
{
    if (canGrow())
        grow(1);
}
bool Grass::reproduce()
{
    if (canReproduce())
    {
        Square* spreadTo=loc->randNeighbor();
        if (spreadTo->isError())
        {
            cout<<"randNeighbor returned squerror\n";
            exit(2);
        }
        if (canGrowOn(spreadTo->getTerrain()->getType()))
        {
            if (requisitionWater(3*moistureToLengthRatio()))
            {
                if (spreadTo->getTerrain()->isCovering())
                {
                    Covering* terr=(Covering*)spreadTo->getTerrain();
                    terr->changeWhatsUnder(ThingType::Grass_T);
                }
                else
                    spreadTo->setTerrain(new Grass());
                return true;
            }
        }
    }
    return false;
}
kilogram Grass::saturation() const
{
    return getType()->saturation;// + saturationFromHeight();
}
kilogram Grass::saturationFromHeight() const
{
    return 0;//height/100;
}
//accessors
void Grass::printInfo() const
{
    Terrain::printInfo();
    cout<<"    Height="<<length<<endl;
}
Color Grass::burnColor() const
{
    return Color(200,100,10);
}
Color Grass::getColor() const
{
    if (burning())
        return Color(200,100,10);
    else
        return (getType()->color->avg(ThingType::Dirt_T->color,length/200.0));
}
bool Grass::canGrowOn(TerrainType* type)
{
    if (type->equals(ThingType::Snow_T))
        return true;
    if (type->equals(ThingType::Dirt_T))
        return true;
    return false;
}