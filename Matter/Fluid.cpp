/* 
 * File:   Fluid.cpp
 * Author: Isaac
 * 
 * Created on November 9, 2013, 2:47 PM
 */

#include "Fluid.h"
#include "../World/Map.h"
#include "../World/Grid.h"

Fluid::Fluid() 
{
    construct();
}
void Fluid::construct()
{
    heat=Map::getDefaultHeat();
    mass=0;
    velocity=new FluidVel();
    loc=Grid::squerror;
}
Fluid::~Fluid() 
{
    delete velocity;
}
void Fluid::printInfo() const
{
    cout<<"    Mass="<<mass<<endl;
    if (mass>0 || Util::bad(mass))
    {
        cout<<"    Heat="<<heat<<endl;
        cout<<"    Velocity:\n";velocity->printInfo();
    }
}
void Fluid::giveMass(float amt)
{
    mass+=amt;
    Util::ensurePositive(mass);
}
void Fluid::giveHeat(float amt)
{
    heat+=amt;
    Util::ensureAbove(mass,1);
}
void Fluid::setVelocity(FluidVel* set)
{
    delete velocity;
    velocity=set;
}