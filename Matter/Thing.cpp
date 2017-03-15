/* 
 * File:   Thing.cpp
 * Author: Isaac
 * 
 * Created on October 3, 2013, 11:33 PM
 */
#include <limits.h>
#include <iostream>

#include "Thing.h"

#include "../_.h"


using namespace std;
/*--------Static----------------*/
int Thing::curID=-1;

/*--------Member-------------*/
Thing::Thing()
{
    construct();
}
Thing::Thing(float setHeat)
{
    construct();
    heat=setHeat;
}
Thing::Thing(const Thing& orig) 
{
    makePropertiesSameAs(&orig);
    assignID();
}
void Thing::construct()
{   
    loc=Grid::squerror;
    references=0;
    assignID();
    heat=Map::getDefaultHeat();
}
Thing* Thing::clone() const
{
    Thing* copy=getType()->getInstance();
    copy->makePropertiesSameAs(this);
    return copy;
}
void Thing::makePropertiesSameAs(const Thing* orig)
{
    loc=orig->loc;
    heat=orig->heat;
}
Thing::~Thing() 
{
    if (references!=0 && !Driver::ended)
    {
        cout<<"Thing deleted with "<<(int)references<<" refs left over\n";
//        exit(0);
    }
}
//references shit
void Thing::deleteRef()
{
    references--;
    if (references==0 && loc->isError())
        delete this;
}
void Thing::banishFromSquare()
{
    loc=Grid::squerror;
    if (references==0)
        delete this;
}
//doers
void Thing::assignID() 
{
    id=curID;
    if (curID==INT_MAX)
    {
        cout<<"Halfway out of IDs"<<endl;
        curID=INT_MIN;
    }
    else if (curID==-2)
    {
        cout<<"Completely out of Thing IDs"<<endl;
        exit(0);
    }
    curID++;
}
void Thing::run()
{
    handlePhysics();
    update();
}
void Thing::handlePhysics()
{
    calcHeat();
    if (burning())
        burn();
}
void Thing::calcHeat()
{
    float area=surfaceArea();
    Matter::exchangeHeat(loc->getSky(),.5,area);
    Matter::exchangeHeat(loc->getTerrain(),.2,area);
}
void Thing::handleFluidForces()
{
    if (underwater()) 
    {
        Liquid* liquid=loc->getLiquid();
        getPushed(liquid->getVelocity(),liquid->getTotalMass());
    }
    else 
    {
        Sky* sky=loc->getSky();
        getPushed(sky->getVelocity(),sky->getMass());
    }
}
void Thing::getPushed(const FluidVel* vel,float fluidMass)
{
    float coef=getDragCoefficient()*sideSurfaceArea();
    
    double xVel=vel->xSum();
    double yVel=vel->ySum();
    xVel*=coef;
    yVel*=coef;
    if (xVel>0)
        push(pow(xVel,2),Dir::East);
    else if (xVel<0)
        push(-pow(xVel,2),Dir::West);
    if (yVel>0)
        push(pow(yVel,2),Dir::South);
    else if (yVel<0)
        push(-pow(yVel,2),Dir::North);
}
//graphics
void Thing::paint()
{
    if (displayType==DisplayType::Normal)
    {
        paintNormal();
    }
}
void Thing::paintNormal()
{
    if (loc->getLiquid()->colorAlpha() <250)
        draw();
}
void Thing::draw()
{
    Draw::setColor(getColor());
    if (getType()->round)
        loc->fillCircle();
    else
        loc->fillRect();
}
void Thing::printInfo()const
{
    cout<<"  "<<getType()->toString()<<endl;
    cout<<"    ID= "<<id<<endl;
    cout<<"    Heat= "<<heat<<endl;
}
//setters

//accessors

Color Thing::getColor() const
{
//    cout<<"color="<<getType()<<endl;
    return *(getType()->color);
}
bool Thing::isDead()const
{
    return loc->isError();
}
bool Thing::underwater() const
{
    return loc->getTerrain()->metersOfWaterAbove()>height();
}
/*--------------STATIC-------------------*/
