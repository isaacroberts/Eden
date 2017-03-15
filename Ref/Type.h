/* 
 * File:   ThingType.h
 * Author: Isaac
 *
 * Created on October 4, 2013, 12:35 PM
 */

#ifndef THINGTYPE_H
#define	THINGTYPE_H

#include "../Gui/Color.h"
#include "Earth.h"
#include "Util.h"

class Thing;
class Terrain;
class Liquid;
struct LiquidAmt;
class TerrainType;

float applySunReceptivityVariance(float factor);
float applySpecHeatRateFactor(float specHeat);
class LiquidType 
{
public:
    float freezePoint,boilingPoint;
    float specificHeat,sunReceptivity;
    float flowRate,density;
    Color* color;
private:
    short id;
    LiquidType(float freezing,float boiling,float specHeat,float sunRecep,
                float setFlowRate,float setDensity,Color* setColor,short setId) 
    {
        freezePoint=freezing;
        boilingPoint=boiling;
        specificHeat=applySpecHeatRateFactor(specHeat);
        sunReceptivity=applySunReceptivityVariance(sunRecep);
        flowRate=setFlowRate;
        density=setDensity;
        color=setColor;
        id=setId;
    }
public:
    virtual ~LiquidType() {
        delete color;
    }
    Liquid* getInstance();
    string toString();
    static LiquidType *Water_T,*Lava_T,*Blood_T;
    static void initialize();
};
class ThingType 
{
public:
    bool round;//whether is drawn as a circle
    float flashPoint;//the point it starts to burn (K)
    float specificHeat;//the amount of heat "inertia" it has
    float density;//kg/m^3
    Color* color;
    string name;
protected:
    ThingType() {}
    ThingType(bool circle,
            float setBurnPoint,float setSpecHeat,
            float setDensity,
            Color* setColor,string setname)
    {
        round=circle;
        flashPoint=setBurnPoint;
        specificHeat=applySpecHeatRateFactor(setSpecHeat);
        density=setDensity;
        color=setColor;
        name=setname;
    }
    virtual ~ThingType()
    {
        delete color;
    }
    virtual bool terrain() {return false;}
public:
    inline string toString()
    {
        return name;
    }
    Thing* getInstance();
    inline bool equals(ThingType* other) {
        return this==other;
    }
//static
    static ThingType *None;
    static ThingType *Rock_T;
    static ThingType *Tree_T,*Shrub_T;
    static ThingType *Fruit_T,*Roots_T;
    static ThingType *Animal_T;
    static TerrainType *Dirt_T,*Grass_T;
    static TerrainType *Spring_T,*Pit_T;
    static TerrainType *Sand_T,*Glass_T;
    
    static TerrainType *Snow_T;
    static TerrainType *Granite_T;
//ThingType(bool land,bool circle,float setBurnPoint,float setSpecHeat,Color* setColor,short setID)
    static void initialize();
    static void end();
};
class TerrainType : public ThingType
{
public:
    float erosionRate;
    kilogram saturation;//in meters of liquid
    float sunReceptivity;//a factor applied to the sun taken in from heat
    float friction;//
    //should be between 0 and 1. will be fit to a smaller range by applySunReceptivityVariance()
    TerrainType(
            float setBurnPoint,float setSpecHeat,
            float sunRecep,
            float setErosionRate,kilogram setSaturation,
            float coeffFriction,
            float setDensity,
            Color* setColor,string setname)
    {
        color=setColor;
        round=false;
        name=setname;
        //thermodynamics
        flashPoint=setBurnPoint;
        specificHeat=applySpecHeatRateFactor(setSpecHeat);
        //sun
        sunReceptivity=applySunReceptivityVariance(sunRecep);
        //land
        erosionRate=setErosionRate;
        saturation=setSaturation;
        friction=coeffFriction;
        //misc
        density=setDensity;
    }
    virtual ~TerrainType() {
    }
    bool terrain(){return true;}
    Terrain* getInstance();
};
class FruitType 
{
public:
    float density;//kg/m^3
    Color* color;
    string name;
    float height;//m (while laying down, however it would fall)
    float volume;//m
    long initialEnergy;//in joules
private:
    FruitType (string setName,float setDens,float setHeight,float setVol,
            long setInitialEnergy,
             Color* setCol)
    {
        color=setCol;
        density=setDens;
        name=setName;
        height=setHeight;
        volume=setVol;
        initialEnergy=setInitialEnergy;
    }
public:
    virtual ~FruitType() {
        delete color;
    }
    static FruitType *Apple,*Banana,*Coconut;
    static void initialize();
};
#endif	/* THINGTYPE_H */

