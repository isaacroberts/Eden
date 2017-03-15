/* 
 * File:   Hell.cpp
 * Author: Isaac
 * 
 * Created on November 15, 2013, 7:15 PM
 */

#include "Hell.h"
#include "../World/Map.h"
#include "../main.h"

using namespace std;

Hell::Hell() {
}
Hell::~Hell() {
}

float Hell::heat()
{
    return 1500;
}
float Hell::humidity()
{
    return 0;
}
Terrain* Hell::getDefaultTerrain()
{
    return new Granite();
}
Liquid* Hell::getDefaultLiquid()
{
    return new Lava();
}
void Hell::setupWorld()
{
    Terrain::elevationDrawSlope=3;
}
void Hell::genElevation()
{
    Map::makeFluxMountains(20,12,6);
    Map::makeCircleMountains(.001,3,20);
}
void Hell::genTerrain()
{
    Map::fillWater(-20);
}
void Hell::genLiquid()
{
    Map::placeWaterBlocks(true,2);
    Map::placeWaterBlocks(false,5);
    for (int x=0;x<GRID.xAmt;++x)
    {
        for (int y=0;y<GRID.yAmt/2;++y)
        {
            GRID.get(x,y)->replaceLiquid(new Blood());
        }
    }
}
void Hell::genOccupants()
{
    Map::makeOccupants(new Rock(),3,3);
}



