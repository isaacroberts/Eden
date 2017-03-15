/* 
 * File:   Map.h
 * Author: Isaac
 *
 * Created on October 3, 2013, 8:03 PM
 */

#ifndef MAP_H
#define	MAP_H

#include "Square.h"
#include "../Matter/_.h"
#include "../Biome/_.h"
#include "../Ref/Type.h"

class Map 
{
public:
    static Animal* animal;
//    friend class Biome;
    static Biome* biome;
    static void makeWorld();
    
    static void draw();
    
    static void makePeak(float height,int radius,Square* center);
    static void makeRecursivePeak(float height,int radius,Square* center);
    
    static void genTerrain(Square* startPoint,const Terrain* set,int size);
    static void genTerrain(Square* startPoint,TerrainType* set,int size);
    static void genTerrain(Square *startPoint,const Terrain* set,float radius,float chaining);
    static void genTerrain(Square *startPoint,TerrainType* set,float radius,float chaining);

    static void makeForest(Square* startPoint,int size,FruitType* type);
    static Tree* makeTree(Square* where,FruitType* type,int height);
    
    static Terrain* getDefaultTerrain();
    static float getDefaultHumidity();
    static float getDefaultHeat();
    static Liquid* getDefaultLiquid();
    static void saturateWorld(float saturationPercentage);
    static pair<float,float> getWorldElevationRange();
public:
    static void makeOccupants(Thing* make,float amtPerHundred,float baseAmtPerHundred);
    static void makeCircleMountains(double peakAmtFactor,double radiusFactor,double peakFactor);
    static void makeFluxMountains(double mounds,int maxResolution,int smoothing);
    static void makeSlope(Square* current,Dir *direction,float deltaHeight,float slope,int xDistFromCenter,int yDistFromCenter);
    static Square* getLocalPeak(bool up,Square* startPoint);//startPoint=NULL for random
    static void placeWaterBlocks(bool spring,int amt);//,double loadingStart,double loadingRange);
    static void fillWater(float level);
    static void fillTerrain(float level,Terrain* fillWith,bool above,bool install);
    
private:
    static pair<double,int> getForestGenerationParameters(int size);
};

#endif	/* MAP_H */

