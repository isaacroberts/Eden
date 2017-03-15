/* 
 * File:   Grass.h
 * Author: Isaac
 *
 * Created on October 5, 2013, 2:18 PM
 */

#ifndef GRASS_H
#define	GRASS_H

#include "Terrain.h"
#include "Plant.h"
#include "../Gui/Draw.h"

class Grass : public Terrain, public Plant
{
public:
    Grass();
    Grass(Square* setloc);
    Grass* clone() const;
    virtual ~Grass();
    virtual TerrainType* getType()const {
        return ThingType::Grass_T;
    }
    float height()const{return elevation+length/100.0;}
    float surfaceArea()const {
        return 1+length/25.;
    }
    void construct();
    virtual void printInfo()const;
    virtual Color burnColor()const;
    virtual Color getColor() const;
    virtual kilogram saturation() const;
    virtual kilogram  saturationFromHeight()const;
    bool isDead() const{
        return length<=0 || Thing::isDead();
    }
    inline void setHeight(int set) {length=set;}
//    void changeHeight(int amt);
    virtual void grow(int amt);
    virtual void grow();
    virtual float heatToLengthRatio();
    virtual float moistureToLengthRatio();
    virtual bool canGrowOn(TerrainType* type);
    static const int GROWTH_FREQ,REPRODUCE_FREQ;
    virtual bool canGrow()const;
    virtual bool canReproduce()const;
    bool isAllocated()const{return true;}
protected:
    virtual bool reproduce();
    virtual void update();
    virtual void burn();
private:
};

#endif	/* GRASS_H */

