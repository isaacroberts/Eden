/* 
 * File:   Snow.cpp
 * Author: Isaac
 * 
 * Created on November 3, 2013, 6:40 PM
 */

#include "Snow.h"
#include "../World/Square.h"
#include "../main.h"

Snow::Snow() 
{
    construct();
}
Snow::Snow(TerrainType* underSnow) 
{
    construct();
    under=underSnow;
}
Snow::Snow(Terrain* orig) 
{
    freeze(orig);
}
void Snow::replace(Terrain* other,float setDepth) {
    Covering::replace(other);
    depth=setDepth;
}
void Snow::freeze(Terrain* toFreeze)
{
    Covering::replace(toFreeze);
    loc->getLiquid()->setMass(0);
    Liquid* liqFreeze=toFreeze->getLoc()->getLiquid();
    if (liqFreeze->getLiquidType()==LiquidType::Water_T)
        depth=float(liqFreeze->getMass())/LiquidType::Water_T->density;
}
void Snow::construct()
{
    Covering::construct();
    depth=0;
}
Snow::~Snow() {
}
Snow* Snow::clone() const
{
    Snow* copy=new Snow();
    copy->makePropertiesSameAs(this);
    copy->setDepth(depth);
    copy->under=under;
    return copy;
}
void Snow::update()
{
    meltAndFreeze();
}
void Snow::meltAndFreeze()
{
    Liquid* liquid=loc->getLiquid();
    long meltRate=(heat-LiquidType::Water_T->freezePoint);
    Util::ensureBelow(meltRate,depth*LiquidType::Water_T->density);
    Util::ensureAbove(meltRate,-liquid->getMass());
    depth-=float(meltRate)/LiquidType::Water_T->density;
    liquid->changeMass(meltRate);
//    heat-=meltRate/1000;
    if (depth<=0.001)
    {
        GRID.queueTerrainReplacement(under->getInstance());
    }
}
void Snow::erode(float amt) {
    if (depth>amt)
        depth-=amt;
    else
    {
        amt-=depth;
        depth=0;
        elevation-=amt;
    }
    if (depth<=0.001)
    {
        GRID.queueTerrainReplacement(under->getInstance());
    }
}
void Snow::draw()
{
    Draw::setColor(under->color);
    loc->fillRect();
    Draw::setColor(getType()->color,Color::colorBound(depth*50 +10));
    loc->fillRect();
}
void Snow::printInfo()const
{
    Covering::printInfo();
    cout<<"    Depth = "<<depth<<endl;
}