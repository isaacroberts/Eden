/* 
 * File:   Fruit.cpp
 * Author: Isaac
 * 
 * Created on November 20, 2013, 2:54 PM
 */

#include "Fruit.h"

#include "Tree.h"

#include "../Gui/Draw.h"
#include "../World/Square.h"


Fruit::Fruit(FruitType* setType) : Mobador()
{
    type=setType;
    energy=type->initialEnergy;
}
Fruit::~Fruit() 
{
}
const joule decayRate=1300;//joules
void Fruit::update()
{
    //TODO : figure out why apple vibrate on trees
    loc->requireRedraw();
    energy-=decayRate;
    Util::ensurePositive(energy);
    if (energy<decayRate)//if energy will run out by next step
    {
//        if (Util::everyNth(3,loc->getHash()))
        {
            if (canSproutOn(loc))
            {
                Tree* tree=new Tree(type);
                loc->addOccupant(tree);
            }
        }
    }
}
bool Fruit::canSproutOn(Square* place) const
{
    if (place->isError())
        return false;
    if (!canSproutOn(place->getTerrain()->getType()))
        return false;
    if (place->hasOccOfTypes((ThingType*[])
        {ThingType::Roots_T,ThingType::Shrub_T},2))
        return false;
    return true;
}
bool Fruit::canSproutOn(TerrainType* type)const {
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
void Fruit::calcHeat()
{
    heat=loc->getSky()->getHeat();
}
void Fruit::burn()
{
    const float burnRate=1000;//in joules
    energy-=burnRate;
    loc->getSky()->addHeatEnergy(burnRate);
    heat=loc->getSky()->getHeat();
}
void Fruit::draw()
{
    int cx=loc->px();
    int cy=loc->py();
    int cDx=float(xPos)/256.0 * Square::squareSize;
    int cDy=float(yPos)/256.0 * Square::squareSize;
    //fixes apples blinking from overlapping squares
    Util::ensureAbove(cDx,Square::quarterSquareSize);
    Util::ensureAbove(cDy,Square::quarterSquareSize);
    Util::ensureBelow(cDx,Square::quarterSquareSize*3);
    Util::ensureBelow(cDy,Square::quarterSquareSize*3);
    cx+=cDx;
    cy+=cDy;
    Draw::setColor(getColor());
    Draw::circle(cx,cy,Square::quarterSquareSize);
}
Color Fruit::getColor() const
{
    if (burning()) {
        return Color(100,100,250);
    }
    Color col=*type->color;
    float percentEnergy=energy;
    percentEnergy/=type->initialEnergy;
    col.red*=percentEnergy;
    col.grn*=percentEnergy;
    col.blu*=percentEnergy;
    percentEnergy*=5;
    if (percentEnergy<1)
        col.alpha*=percentEnergy;
    return col;
}
bool Fruit::isDead()const
{
    return loc->isError() || energy<=0;
}