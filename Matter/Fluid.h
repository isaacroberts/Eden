/* 
 * File:   Fluid.h
 * Author: Isaac
 *
 * Created on November 9, 2013, 2:47 PM
 */

#ifndef FLUID_H
#define	FLUID_H

#include "Matter.h"
class Square;

class Fluid :public Matter
{
public:
    Fluid();
    void construct();
    virtual ~Fluid();
    //info getters
    virtual void printInfo()const;
    virtual float getVolume()const{return 1;}
    virtual float getDensity()const{return mass/getVolume();}
    inline float pressure()const{return getDensity()*heat;}
    //accessors
    inline float getMass()const{return mass;}
    inline FluidVel* getVelocity(){return velocity;}
    inline const FluidVel* getVelocity()const{return velocity;}
    //setters
    inline void setLoc(Square* set){loc=set;}
    virtual void giveMass(float amt);
    virtual void giveHeat(float amt);
    inline void setMass(float set){mass=set;}
    virtual void zeroMass(){mass=0;}
    virtual void changeMass(float amt){mass+=amt;
            Util::ensurePositive(mass);}
    void setVelocity(FluidVel* set);
protected:
    float mass;//in kilograms
    FluidVel* velocity;//in kg/s
    Square* loc;
    
};

#endif	/* FLUID_H */

