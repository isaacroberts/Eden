/* 
 * File:   Type.cpp
 * Author: Isaac
 * A place where all Types can live in harmony
 * Its also easier to look at all climate-related variables 
 * side-by-side and tweak them
 * Created on October 4, 2013, 12:35 PM
 */

#include "Type.h"
#include "../Matter/_.h"
#include "../World/Animalia.h"

ThingType* ThingType::None;
ThingType* ThingType::Rock_T;
ThingType* ThingType::Tree_T;
ThingType* ThingType::Shrub_T;
ThingType* ThingType::Fruit_T;
ThingType* ThingType::Roots_T;

ThingType* ThingType::Animal_T;

TerrainType* ThingType::Dirt_T;
TerrainType* ThingType::Grass_T;
TerrainType* ThingType::Spring_T;
TerrainType* ThingType::Pit_T;
TerrainType* ThingType::Sand_T;
TerrainType* ThingType::Glass_T;
TerrainType* ThingType::Granite_T;

TerrainType* ThingType::Snow_T;

LiquidType* LiquidType::Water_T;
LiquidType* LiquidType::Lava_T;
LiquidType* LiquidType::Blood_T;

FruitType* FruitType::Apple;
FruitType* FruitType::Banana;
FruitType* FruitType::Coconut;

void LiquidType::initialize()
{
//FluidType(freeze,boilPoint,specHeat,sunRecep,flowRate,density)
    Water_T=new LiquidType(273,373,4.184,.5,1,1000,
            new Color(0,0,200),0);
    Lava_T=new LiquidType(1000,200000,8,.9,.1,10000,
            new Color(255,64,0),1);
    Blood_T=new LiquidType(270,370,3.6,.7,.6,1050,//blood is only slightly thicker than water
            new Color(150,0,0),2);
}
void ThingType::initialize()
{   
//ThingType(circle,burnPoint,specHeat,density,Color,ID)
    //None placeholder Thing
    None=new ThingType(false,1,666,1,new Color(),"None");// i use 666 as an error number because its easy to spot
    //occupants
    Rock_T=new ThingType(false,1000,4,2700,new Color(100,100,100),"Rock");
    Tree_T=new ThingType(true,460,4,600,new Color(100,50,0),"Tree");
    Shrub_T=new ThingType(true,430,2,400,new Color(100,80,0),"Shrub");
    
    Fruit_T=new ThingType(true,500,5,742,new Color(250,0,0),"Fruit");
    Roots_T=new ThingType(false,475,3.2,1230,new Color(80,40,0),"Roots");
    
    Animal_T=new ThingType(true,500,4,900,new Color(150,150,0),"Animal");
    //terrains
//TerrainType(burnPoint(Kelvin),specHeat,sunRecep,erosionRate,
  //               saturation(kg),friction,density(kg//m^3),color,ID)
    Dirt_T=new TerrainType(475,3,.4,1,3000,.1,1220,new Color(130,75,25),"Dirt");
    Grass_T=new TerrainType(500,3,.5,.8,5000,.1,1225,new Color(0,100,0),"Grass");

    Spring_T=new TerrainType(LiquidType::Water_T->freezePoint,
            3,.2,0,1000,.1,1000,new Color(50,50,250),"Spring");
    Pit_T=new TerrainType(520,3,.8,0,100000,.1,1000,new Color(70,10,0),"Pit");

    Sand_T=new TerrainType(1650,3,.2,2,7000,.1,1555,new Color(200,150,0),"Sand");
    Glass_T=new TerrainType(3000,2,.1,0.001,0,.1,2400,new Color(100,120,200),"Glass");
    
    Snow_T=new TerrainType(LiquidType::Water_T->freezePoint
            ,LiquidType::Water_T->boilingPoint
            ,.1,1.5,3000,.1,900,new Color(200,200,250),"Snow");
    
    Granite_T=new TerrainType(1000,.79,.7,.05,50,.1,2700,new Color (100,100,100),"Granite");
}
void FruitType::initialize()
{
    //fruitType(name,dens,height,volume,energy,color)
    Apple=new FruitType("Apple",276,.1,.00052,4E+5,new Color(255,0,0));
    Banana=new FruitType("Banana",850,.05,.0002,4.4E+5,new Color(255,255,0));
    Coconut=new FruitType("Coconut",565,.3,.014,6.6E+5,new Color(150,75,0));
}
void ThingType::end() 
{
    delete LiquidType::Water_T;
    delete LiquidType::Blood_T;
    delete LiquidType::Lava_T;
    delete None;
    delete Rock_T;
    delete Tree_T; delete Shrub_T;
    delete Fruit_T;
    delete Animal_T;
    delete Dirt_T; delete Grass_T;
    delete Spring_T; delete Pit_T;
    delete Sand_T; delete Glass_T;
    delete Snow_T; delete Granite_T;
    delete FruitType::Apple; delete FruitType::Banana;
    delete FruitType::Coconut;
}
float applySunReceptivityVariance(float sunFactor)
{
    const float varianceRange=.3;
    return sunFactor*varianceRange + (1-varianceRange)/2.0;
}
float applySpecHeatRateFactor(float specHeat)
{
    return (specHeat)/10;
}
Thing* ThingType::getInstance()
{
    if (this==Rock_T)
        return new Rock();
    else if (this==Tree_T)
        return new Tree();
    else if (this==Shrub_T)
        return new Shrub();
    else if (this==Fruit_T)
        return new Fruit(FruitType::Apple);
    else if (this==Roots_T)
        return new Roots();
    else if (this==Animal_T)
        return new Animal(Animalia::gerbil);//dangerous later on
    else if (this==Dirt_T)
        return new Dirt();
    else if (this==Grass_T)
        return new Grass();
    else if (this==Spring_T)
        return new Spring();
    else if (this==Pit_T)
        return new Pit();
    else if (this==Sand_T)
        return new Sand();
    else if (this==Glass_T)
        return new Glass();
    else if (this==Snow_T)
        return new Snow();//dangerous?
    else if (this==Granite_T)
        return new Granite();
    else if (this==None)
        return new NoThing();
    else
        cout<< "ERROR: NO INSTANCE FOR THINGTYPE "<<name<<endl;
        exit(1);
}
Terrain* TerrainType::getInstance()
{
    if (this==Dirt_T)
        return new Dirt();
    else if (this==Grass_T)
        return new Grass();
    else if (this==Spring_T)
        return new Spring();
    else if (this==Pit_T)
        return new Pit();
    else if (this==Sand_T)
        return new Sand();
    else if (this==Glass_T)
        return new Glass();
    else if (this==Snow_T)
        return new Snow();//dangerous?
    else if (this==Granite_T)
        return new Granite();
    else
        cout<< "ERROR: NO INSTANCE FOR TERRAINTYPE "<<name<<endl;
        exit(1);
}
Liquid* LiquidType::getInstance()
{
    switch (id)
    {
        case 0:
            return new Water();
        case 1:
            return new Lava();
        case 2:
            return new Blood();
        default:
            cout<<" ERROR: NO INSTANCE FOR LIQUIDTYPE "<<id<<endl;
            exit(1);
    }
}
string LiquidType::toString()
{
    switch (id)
    {
        case 0:
            return "Water";
        case 1:
            return "Lava";
        case 2:
            return "Blood";
        default:
            cout<<" ERROR: NO NAME FOR LIQUIDTYPE "<<id<<endl;
            exit(1);
    }
}