/* 
 * File:   Mountains.cpp
 * Author: Isaac
 * 
 * Created on November 15, 2013, 6:59 PM
 */

#include "MountainRange.h"
#include "../World/Map.h"
#include "../main.h"

using namespace std;

MountainRange::MountainRange() {
}
MountainRange::~MountainRange() {
}

float MountainRange::heat()
{
    return 278;
}
float MountainRange::humidity()
{
    return 1;
}
Terrain* MountainRange::getDefaultTerrain()
{
    return new Dirt();
}
Liquid* MountainRange::getDefaultLiquid()
{
    return new Water();
}
void MountainRange::setupWorld()
{
    Terrain::elevationDrawSlope=4;
}
void MountainRange::genElevation()
{
    Map::makeFluxMountains(50,10,11);
}
void MountainRange::genTerrain()
{
    Map::genTerrain(GRID.getRandSquare(),ThingType::Grass_T,5,.05);
    pair<float,float> elevRange=Map::getWorldElevationRange();
    float snowLevel=(elevRange.second-elevRange.first)*.7 +elevRange.first;
    Snow* copyFrom=new Snow(ThingType::Dirt_T);
    copyFrom->setDepth(3);
    copyFrom->setHeat(LiquidType::Water_T->freezePoint-20);
    Map::fillTerrain(snowLevel,copyFrom,true,true);
    delete copyFrom;
}
void MountainRange::genLiquid()
{
    Map::placeWaterBlocks(true,5);
    Map::placeWaterBlocks(false,5);
    Map::saturateWorld(.9);
}
void MountainRange::genOccupants()
{
    Map::makeOccupants(new Rock(),3,4);
    Map::makeOccupants(new Tree(FruitType::Coconut,4000),3,2);
}


