/* 
 * File:   Water.h
 * Author: Isaac
 *
 * Created on October 11, 2013, 11:54 AM
 */

#ifndef WATER_H
#define	WATER_H

#include "Liquid.h"
class Terrain;

class Water : public Liquid
{
protected:
//    Vector* velocity;
public:
    Water();
    virtual Water* clone()const;
    virtual ~Water();
    
    virtual void update();
    static float getErosion(float moistureFlow,Terrain* from);
    //settors
    //accessors
    LiquidType* getLiquidType()const{return LiquidType::Water_T;}
    Color::hue colorAlpha()const;
//    inline virtual Vector* getVelocity()const{return velocity;}
    
protected:
    
    void evaporate();
private:
};

#endif	/* WATER_H */

