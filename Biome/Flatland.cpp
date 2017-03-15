/* 
 * File:   Flatland.cpp
 * Author: Isaac
 * 
 * Created on November 15, 2013, 7:47 PM
 */

#include "Flatland.h"
#include "../World/Map.h"
Flatland::Flatland() {
}

Flatland::~Flatland() {
}
float Flatland::heat()
{
    return 280;
}
float Flatland::humidity()
{
    return 0;
}
void Flatland::setupWorld()
{
    Terrain::elevationDrawSlope=5;
}
Terrain* Flatland::getDefaultTerrain()
{
    return new Glass();
}
Liquid* Flatland::getDefaultLiquid()
{
    return new Water();
}
void Flatland::genOccupants()
{
    Map::makeOccupants(new Fruit(FruitType::Apple),2,1);
}