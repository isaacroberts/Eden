/* 
 * File:   Forest.cpp
 * Author: Isaac
 * 
 * Created on November 15, 2013, 5:29 PM
 */
#include "Forest.h"
#include "../World/Map.h"
#include "../World/Animalia.h"
#include "../main.h"
Forest::Forest() {
}
Forest::~Forest() {
}
float Forest::heat()
{
    return 293;
}
float Forest::humidity()
{
    return .5;
}
Terrain* Forest::getDefaultTerrain()
{
    Grass* deflt=new Grass();
    deflt->setHeight(150);
    return deflt;
}
Liquid* Forest::getDefaultLiquid()
{
    return new Water();
}
void Forest::setupWorld()
{
    Terrain::elevationDrawSlope=4;
}
void Forest::genElevation()
{
    Map::makeCircleMountains(.05,12,20);
    Map::makeFluxMountains(50,10,20);
}
void Forest::genTerrain()
{
}
void Forest::genLiquid()
{
    Map::placeWaterBlocks(true,2);
    Map::placeWaterBlocks(false,4);
    Map::saturateWorld(.8);
}
void testForestGeneration()
{
    int runningArea=0;
    int trials=150;
    int size[]=
        {8000,9000,10000,11000,12000};
    int sizeAmt=5;
    double totalPercentDif=0;
    for (int s=0;s<sizeAmt;s++)
    {
        int amtOOB=0;
        for (int n=0;n<trials;++n)
        {
            int area=0;
            Map::genTerrain(NULL,TerrainType::Sand_T,size[s]);
            for (int x=0;x<GRID.xAmt;x++)
            {
                for (int y=0;y<GRID.yAmt;++y)
                {
                    Square* sqr=GRID.get(x,y);
                    if (sqr->getTerrain()->isA(TerrainType::Sand_T))
                    {
                        area++;
                        sqr->clearTerrain();
                    }
                }
            }
            if (abs(area-size[s])/double(size[s]) >= .5 )
                amtOOB++;
            runningArea+=area;
        }
        runningArea/=trials;
        cout<<"Intended Size = "<<size[s]<<endl;
        cout<<"    -Avg Size = "<<runningArea<<endl;
        double percentDiff=(runningArea-size[s])/double(size[s]);
        cout<<"    -Percent diff = "<<percentDiff<<endl;
        percentDiff=abs(percentDiff);
        totalPercentDif+=percentDiff;
        cout<<"    -Amt of Outliers = "<<amtOOB<<endl;
    }
    totalPercentDif/=sizeAmt;
    cout<<"Average percent difference = "<<totalPercentDif<<endl;
    exit(0);
}
void Forest::genOccupants()
{
//    testForestGeneration();
    Map::makeForest(NULL,2000,FruitType::Apple);
    Map::makeOccupants(new Rock(),2,0);
//    Map::makeOccupants(new Tree(FruitType::Banana,4000),3,4);
}
