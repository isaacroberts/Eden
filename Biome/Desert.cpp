/* 
 * File:   Desert.cpp
 * Author: Isaac
 * 
 * Created on November 15, 2013, 6:28 PM
 */

#include "Desert.h"
#include "../World/Map.h"

using namespace std;

Desert::Desert() {
}
Desert::~Desert() {
}
float Desert::heat()
{
    return 303;
}
float Desert::humidity()
{
    return .005;
}
Terrain* Desert::getDefaultTerrain()
{
    return new Sand();
}
Liquid* Desert::getDefaultLiquid()
{
    return new Water();
}
void Desert::setupWorld()
{
    Terrain::elevationDrawSlope=6;
}
void Desert::genElevation()
{
    Map::makeFluxMountains(400,15,20);
}
void Desert::genTerrain()
{
}
void Desert::genLiquid()
{
//    float avgElev=0;
    //avgElev should be zero right after mountains() bc it normalizes avgElev to zero
    pair<float,float> elevRange=Map::getWorldElevationRange();
    float waterLevel=(elevRange.second-elevRange.first)*.05 +elevRange.first;
    Map::fillWater(waterLevel);
    Grass* copyFrom=new Grass();
    copyFrom->setHeight(50);
    float grassLevel=(elevRange.second-elevRange.first)*.06 +elevRange.first+5;
    Map::fillTerrain(grassLevel,copyFrom,false,false);
    delete copyFrom;
}
void Desert::genOccupants()
{
    Map::makeOccupants(new Rock(),1,0);
    Tree* occupant=new Tree();
    occupant->setLength(1000);
    Map::makeOccupants(occupant,1,2);
    Shrub* shrub=new Shrub();
    shrub->setLength(3);
    Map::makeOccupants(shrub,3,2);
}