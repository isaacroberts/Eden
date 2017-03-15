/* 
 * File:   Shoehorn.h
 * Author: Isaac
 *
 * Created on November 18, 2013, 12:44 PM
 */

#ifndef MATTER_H
#define	MATTER_H

#include "../Ref/_.h"

class Matter 
{
public:
    Matter();
    Matter(const Matter& orig);
    virtual ~Matter();
    //doers
//    virtual void exchangeHeat(Matter* with,float contactArea) {exchangeHeat(with,1);}
    virtual void exchangeHeat(Matter* with,float rate,float contactArea);
    //getters
    virtual float getSpecHeat()const=0;
    virtual float heatMass()const{return getMass()*getSpecHeat();}
    inline float heatMomentum()const{return heatMass()*heat;}
    virtual float getMass()const=0;
    float getHeat()const{return heat;}
    //setters
    inline void changeHeat(float amt){heat+=amt;
                Util::ensureAbove(heat,1); }
    inline void setHeat(float set){heat=set;}
    inline void addHeatEnergy(float amt){//joules
        changeHeat(amt/heatMass());
    }
    virtual void giveHeat(float amt){changeHeat(amt);}
protected:
    float heat;//in Kelvin

};

#endif

