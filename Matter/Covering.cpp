/* 
 * File:   Snow.cpp
 * Author: Isaac
 * 
 * Created on November 3, 2013, 6:37 PM
 */

#include "Snow.h"

Covering::Covering() 
{
    construct();
}
Covering::Covering(Terrain* orig) 
{
    replace(orig);
}
void Covering::replace(Terrain* other)
{
    Terrain::replace(other);
    under=other->getType();
}
void Covering::construct()
{
    Terrain::construct();
    under=ThingType::Dirt_T;
}
Covering::~Covering() 
{
}
void Covering::printInfo() const
{
    Terrain::printInfo();
    cout<<"    Underneath: "<<under->toString()<<endl;
}