/* 
 * File:   Plant.h
 * Author: Isaac
 *
 * Created on November 6, 2013, 5:33 PM
 */

#ifndef PLANT_H
#define	PLANT_H

#include "Thing.h"

class Plant : virtual public Thing
{
public:
    Plant();
    void construct();
    Plant* clone()const=0;
    virtual ~Plant();
    //doers
    static void updateAll();
    virtual void changeLength(int amt);
    virtual bool requisitionWater(float amt);
    virtual void grow(int amt);
    virtual void grow();
    virtual void printInfo()const;
    //information getters
    virtual bool isDead()const {
        return length<=0 || Thing::isDead();
    }
    float height()const{return length/100.0;}
//    virtual float getCalories()=0;
    virtual bool canGrowOn(TerrainType* type)const;
    virtual bool canGrow()const=0;
    virtual bool canReproduce()const=0;
    //accessors
    inline int getLength() {
        return length;
    }
    virtual Color getColor()const;
    virtual Color burnColor()const {
        return Color(250,75,0);
    }
    virtual int heightAlpha()const {
        return 255;
    }
/*pure*/virtual float heatToLengthRatio()=0;
/*pure*/virtual float moistureToLengthRatio()=0;
    bool isPlant(){return true;}
    bool isAllocated()const{return true;}
    //mutators
    void setLength(int set){length=set;}
    
protected:
    virtual void update();
/*pure*/virtual bool reproduce()=0;
    int length;//in cm
    //encouraged to be #define'd to use a different name like leafAmt
};

#endif	/* PLANT_H */

