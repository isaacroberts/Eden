/* 
 * File:   Map.cpp
 * Author: Isaac
 * 
 * Created on October 3, 2013, 8:03 PM
 */
#include <iostream>
#include <math.h>
#include <list>

#include "Map.h"

#include "../main.h"
#include "../Gui/Event.h"
#include "Game.h"

#include "../Matter/_.h"

#include "../Biome/_.h"
#include "Animalia.h"

using namespace std;

Biome* Map::biome=new Forest();
int Terrain::elevationDrawSlope;

Animal* Map::animal=NULL;

void Map::makeWorld()
{
    Earth::setSunAndSpace(getDefaultHeat(),.5);
    biome->setupWorld();
    biome->genElevation();
    //normalize the elevation around 0
    float avgElev=GRID.getChunkElevation(0,0,GRID.xAmt-1,GRID.yAmt-1);
    GRID.changeChunkElevation(0,0,GRID.xAmt-1,GRID.yAmt-1,-avgElev);
    biome->genTerrain();
    biome->genLiquid();
    biome->genOccupants();
    
    animal=new Animal(Animalia::gerbil);
    GRID.getRandSquare()->addOccupant(animal,1);
    
}
void Map::draw()
{
}
void Map::makeOccupants(Thing* occ, float rangePerHundred, float baseAmtPerHundred)
{//deletes copyFrom at end of function
    double hundredsOfSquares=GRID.amt()/100.0;
    int amt=baseAmtPerHundred*hundredsOfSquares;
    amt+=rangePerHundred*Util::randDouble()*hundredsOfSquares;
    for (int a=0;a<amt;a++)
    {
        Square* randSqr=GRID.getRandSquare();
        bool toPlace=true;
        if (occ->isPlant())
        {
            Plant* plant=dynamic_cast<Plant*>(occ);
            if (!plant->canGrowOn(randSqr->getTerrain()->getType()))
                toPlace=false;
        }
        if (toPlace)
            randSqr->addOccupant(occ->clone());
    }
    delete occ;
}
void Map::makeFluxMountains(double mounds,int maxResolution,int smoothing)
{
    Driver::loadingScreen->setTask(LoadingScreen::Mountains);
    mounds*=8;//balances out the (rand()%0.5^3) used
    for (int res=maxResolution;res>0;--res)
    {
        int range=res-1;
        Driver::loadingScreen->setPercentage(maxResolution-res,maxResolution);
        Event::checkForExit();
        for (int s=0;s<smoothing;++s)
        {
//            Eden::loadingScreen->setPercentage((maxResolution-res)*smoothing +s,smoothing*maxResolution);
            //raise/lower chunks of land
            for (int x=0;x<GRID.xAmt;x+=res)
            {
                for (int y=0;y<GRID.yAmt;y+=res)
                {
                    float elev=GRID.getChunkElevation(x,y,GRID.validizeX(x+range),GRID.validizeY(y+range));
                    float avgElev=0;
                    int naybAmt=0;
                    Dir *naybDir=Dir::North;
                    for (int n=0;n<4;++n)
                    {//look at the nayboring chunks in the four directions
                        //and average their elevations
                        int nx=GRID.wrapX(x+naybDir->x()*res);
                        int ny=y+naybDir->y()*res;
                        if (ny>-range && ny<GRID.yAmt-1)
                        {
                            if (ny<0)
                                ny=0;
                            avgElev+=GRID.getChunkElevation(nx,ny,
                                GRID.validizeX(nx+range),GRID.validizeY(ny+range));
                            ++naybAmt;
                        }
                        naybDir=naybDir->rotateClockwise();
                    }
                    if (naybAmt>0)
                        avgElev/=naybAmt;
                    else avgElev=elev;
                    float deltaElev=avgElev-elev;
                    if ( res*4>=maxResolution && s*.75<=smoothing)
                        deltaElev+=pow(Util::randDouble()-.5,3)*mounds;
                    GRID.changeChunkElevation(x,y,GRID.validizeX(x+range),GRID.validizeY(y+range),deltaElev);
                }
            }
        }
    }
    Driver::loadingScreen->setPercentage(1);
}
void Map::makeCircleMountains(double peakAmtFactor,double radiusFactor,double peakFactor)
{
    radiusFactor=sqrt(radiusFactor);//so peakHeight can be multiplied by radiuDriver  Game::loadingScreen->setTask(LoadingScreen::Mountains);
    int peakAmt=(GRID.amt())*(Util::randDouble(.01)+.02);
    long time=SDL_GetTicks();
    for (int n=0;n<peakAmt;n++)
    {
        if (freq(n,peakAmt,16))
        {
            Driver::loadingScreen->setPercentage(n,peakAmt);
            Event::checkForExit();
        }
        float radius=(Util::randDouble()*.4)+.8;
        radius*=radiusFactor;
        float peak=(float)(pow(Util::randDouble()-.5f ,3))*8;
        peak*=radius;
        radius*=radius;
        peak*=peakFactor;
        Square* center=GRID.getRandSquare();
        
        makePeak(peak,radius,center);
    }
    Driver::loadingScreen->setPercentage(1);
    long runTime=SDL_GetTicks()-time;
    Event::checkForExit();
}
void Map::makePeak(float height, int radius, Square* center)
{
    if (height==0)
        return;
    if (radius==0)
        radius=1;
    float slope=height/(pow(radius,2));
    vector<Square*>* area=GRID.getSquareOfSquares(center,radius);
    for (int n=0;n<area->size();n++)
    {
        double sqrdDist=Util::sqrdDist(center,area->at(n));
        float elevChange=(float)(height-slope*sqrdDist);
        
        if ((elevChange>0) == (height>0))
        {
            area->at(n)->getTerrain()->changeElevation(elevChange);
        }
    }
}
void Map::makeRecursivePeak(float height, int radius, Square* center)
{
    if (height==0)
        return;
    if (radius==0)
        radius=1;
    center->getTerrain()->changeElevation(height);
    float slope=height/float(radius);
    slope*=abs(slope);
    Dir *dir=Dir::North;
//    cout<<"  slope = "<<slope<<endl;
    for (int rotate=0;rotate<4;++rotate)
    {
        makeSlope(center->transform(dir),dir,height,slope/radius,dir->x(),dir->y());
        dir=dir->rotateClockwise();
    }
}
void Map::makeSlope(Square* current,Dir *dir, float height,float slope, int dx, int dy)
{
    if (current==NULL)
    {
        cout<<"Somehow in makeSlope current=NULL?"<<endl;
        return;
    }
    if (current->isError())
        return;
    double changeInDist=Util::changeInDist(dx,dy,dir->x(),dir->y());
    slope+=(slope>0?changeInDist:-changeInDist);
    height-=slope;
    if (slope!=slope)
    {
        cout<<"Slope is NaN\n";
        return;
    }
    else if (slope==0)
    {
        cout<<"Slope is 0\n";
        return;
    }
    if (slope>=0 && height<=0)
        return;
    if (slope<=0 && height>=0)
        return;
//    cout<<"    slope @ ";current->printString();cout<<endl;
    current->getTerrain()->changeElevation(height);
    makeSlope(current->transform(dir),dir,height,slope,dx+dir->x(),dy+dir->y());
    if (dx==0 || dy==0)
    {
        dir=dir->rotateClockwise();
        makeSlope(current->transform(dir),dir,height,slope,dx+dir->x(),dy+dir->y());
    }
}
void Map::genTerrain(Square* startPoint,const Terrain* set,int size)
{
    pair<double,int> param=Util::getChainingGenerationParameters(size);
    genTerrain(startPoint,set,param.second,param.first);
}
void Map::genTerrain(Square* startPoint,TerrainType* set,int size)
{
    pair<double,int> param=Util::getChainingGenerationParameters(size);
    genTerrain(startPoint,set,param.second,param.first);
}
void Map::genTerrain(Square* startPoint,const Terrain* set, float radius, float chaining)
{
    //chain is a diminishing probability.   
    //size is always greater than pi*(1-log(chain)/log(.9))^2 * rad^2,
        //and always greater than pi*rad^2
    if (!startPoint)
        startPoint=GRID.getRandSquare();
    vector<pair<Square*,float> > centers=vector<pair<Square*,float> >();
    centers.push_back(pair<Square*,float>(startPoint,chaining));
    vector<Square*>* within;
    while (centers.size()>0)
    {
        within=GRID.getSquaresInRadius(centers.at(0).first,radius);
        for (int n=0;n<within->size();n++)
        {
            if (!within->at(n)->getTerrain()->getType()->equals(set->getType()))
            {
                if (Util::randDouble()<centers[0].second)
                {
                    centers.push_back(pair<Square*,float>
                        (within->at(n),centers[0].second*.9));
                }
                within->at(n)->setTerrain(set->clone());
            }
        }
        centers.erase(centers.begin());
    }
    delete within;
}
void Map::genTerrain(Square* startPoint, TerrainType* set, float radius, float chaining)
{
    //chain is a diminishing probability.   
    //size is always greater than pi*(1-log(chain)/log(.9))^2 * rad^2,
        //and always greater than pi*rad^2
    if (!startPoint)
        startPoint=GRID.getRandSquare();
    vector<pair<Square*,float> > centers=vector<pair<Square*,float> >();
    centers.push_back(pair<Square*,float>(startPoint,chaining));
    vector<Square*>* within;
    while (centers.size()>0)
    {
        within=GRID.getSquaresInRadius(centers.at(0).first,radius);
        for (int n=0;n<within->size();n++)
        {
            if (within->at(n)->isError())
            {
                cout<<"getSquaresInRadius giving an error square.\n";
            }
            else if (!within->at(n)->getTerrain()->getType()->equals(set))
            {
                if (Util::randDouble()<centers[0].second)
                {
                    centers.push_back(pair<Square*,float>
                        (within->at(n),centers[0].second*.9));
                }
                within->at(n)->setTerrain(set->getInstance());
            }
        }
        centers.erase(centers.begin());
    }
    delete within;
}
Square* Map::getLocalPeak(bool up, Square* current)
{//finds the lowest local square 
    //(ie, "climbs" up the mountain or down the valley)
    if (current==NULL)
        current=GRID.getRandSquare();
    bool peaked=false;
    while (!peaked)
    {
        peaked=true;
        vector<Square*>* nayb=GRID.getSquareOfSquares(current,3);
        for (int n=0;n<nayb->size();n++)
        {
            if (up)
            {
                if (nayb->at(n)->getTerrain()->getElevation()
                        > current->getTerrain()->getElevation())
                {
                    peaked=false;
                    current=nayb->at(n);
                }
            }
            else
            {
                if (nayb->at(n)->getTerrain()->getElevation()
                        < current->getTerrain()->getElevation())
                {
                    peaked=false;
                    current=nayb->at(n);
                }     
            }
        }
        delete nayb;
    }
    return current;
}
void Map::makeForest(Square* startPoint, int size, FruitType* type)
{
    Driver::loadingScreen->setTask(LoadingScreen::Forest);
    float chaining;
    int radius;
    
    pair<double,int> param=getForestGenerationParameters(size);
    chaining=param.first;
    radius=param.second;
    
    if (startPoint==NULL)
        startPoint=GRID.getRandSquare();
    list<pair<Square*,float> > treePoints=list<pair<Square*,float> >();
    treePoints.push_front(pair<Square*,float>(startPoint,chaining));
    vector<Square*>* within;
    int runningSize=1;
    int currentIter=0;
    makeTree(startPoint,type,6000);
    while (treePoints.size()>0)
    {
        if (currentIter%32==0) {
            Driver::loadingScreen->setPercentage(currentIter,runningSize);
        }
        within=GRID.getSquaresInRadius(treePoints.front().first,radius);
        for (int n=0;n<within->size();n++)
        {
            if (within->at(n)->isnt(treePoints.front().first))
            {//if square isnt the current center being looked at
                if (!within->at(n)->hasOccOfType(ThingType::Roots_T))
                {//if square doesnt have roots already
                    if (Util::randDouble()<treePoints.front().second)
                    {//possibility = center's chaining value
                        //create tree and add it to center list
                        makeTree(within->at(n),type,6000);
                        treePoints.push_back(pair<Square*,float>
                            (within->at(n),treePoints.front().second*.9));
                        runningSize++;
                    }
                }
            }
        }
        treePoints.pop_front();
        currentIter++;
        if (currentIter%16==2)
            Event::checkForExit();
    }
    delete within;
}
Tree* Map::makeTree(Square* loc,FruitType* fruitType,int height)
{
    Tree* tree=new Tree(fruitType,height);
    loc->addOccupant(tree);
    Roots* roots=tree->getRoots();
    int rootAmt=height/500;//kindof the tree growth:root reproduction ratio
    int amtPlaced=0;
    for (int n=0;n<rootAmt/*2 && amtPlaced<rootAmt*/;n++)
    {
        bool repd=roots->forceReproduce();
        if (repd) {
            amtPlaced++;
        }
    }
    if (amtPlaced<rootAmt)
    {
        if (amtPlaced==0) {
//            loc->clearOccupant(tree->getRoots());
            loc->clearOccupant(tree);
            return NULL;
        }
//        tree->setLength((amtPlaced+1)*500);
    }
    return tree;
}
void Map::placeWaterBlocks(bool spring, int amt)//,double loadingStart,double loadingRange)
{
    for (int p=0;p<amt;p++)
    {
//        Eden::loadingScreen->setPercentage
//                (loadingStart+(p/amt)*loadingRange);
        Square* peak=getLocalPeak(spring,NULL);
        if (spring) {
            if (peak->getTerrain()->isA(ThingType::Spring_T))
            {
                peak=peak->transform(Dir::getRandDir());
            }
            peak->setTerrain(new Spring());
        }
        else {
            if (peak->getTerrain()->isA(ThingType::Pit_T))
            {
                peak=peak->transform(Dir::getRandDir());
            }
            peak->setTerrain(new Pit());
        }
    }
//    Eden::loadingScreen->setPercentage(loadingStart+loadingRange);
//    Eden::loadingScreen->display();
}
void Map::fillWater(float level)
{
    for (int x=0;x<GRID.xAmt;++x)
    {
        for (int y=0;y<GRID.yAmt;++y)
        {
            float height=GRID.get(x,y)->getTerrain()->getElevation();
            height=level-height;
            if (height>0)
            {
                height*=GRID.get(x,y)->getLiquid()->getDensity();
                GRID.get(x,y)->getLiquid()->addAndSatMass(height);
            }
        }
    }
}
void Map::fillTerrain(float level, Terrain* copyFrom, bool above,bool install)
{
    for (int x=0;x<GRID.xAmt;++x)
    {
        for (int y=0;y<GRID.yAmt;++y)
        {
            if (GRID.get(x,y)->getTerrain()->getElevation()>level == above)
            {
                if (install)
                    GRID.get(x,y)->installTerrain(copyFrom->clone());
                else
                    GRID.get(x,y)->setTerrain(copyFrom->clone());
            }
        }
    }
}
pair<float,float> Map::getWorldElevationRange()
{//returns pair of elevations {lowestElev,highestElev}
    float minElev,maxElev;
    minElev=maxElev=GRID.get(0,0)->getTerrain()->getElevation();
    for (int x=0;x<GRID.xAmt;++x)
    {
        for (int y=0;y<GRID.yAmt;++y)
        {
            Util::ensureBelow(minElev,GRID.get(x,y)->getTerrain()->getElevation());
            Util::ensureAbove(maxElev,GRID.get(x,y)->getTerrain()->getElevation());
        }
    }
    return pair<float,float>(minElev,maxElev);
}
void Map::saturateWorld(float saturationPercentage)
{
    for (int x=0;x<GRID.xAmt;++x)
    {
        for (int y=0;y<GRID.yAmt;++y)
        {
            Square* loc=GRID.get(x,y);
            loc->getLiquid()->setAndSatMass(
                saturationPercentage * loc->getTerrain()->saturation());
        }
    }
}
Terrain* Map::getDefaultTerrain()
{
    return biome->getDefaultTerrain();
}
Liquid* Map::getDefaultLiquid()
{
    return biome->getDefaultLiquid();
}
float Map::getDefaultHeat()
{
    return biome->heat();
}
float Map::getDefaultHumidity()
{
    return biome->humidity();
}
pair<double,int> Map::getForestGenerationParameters(int size)
    {
        pair<double,int> param;
        if (size>1000)
        {
            param.second=4;// = radius
            param.first=size*1.6e-5 + 2e-2;
        }
        else if (size<100)
        {
            param.first=0;
            param.second=Util::roundUp(sqrt(size/3.14));
        }
        else
        {
            param.second=4;
            param.first=size* 2.3e-5 + 1.42e-2;
        }
        return param;
    }