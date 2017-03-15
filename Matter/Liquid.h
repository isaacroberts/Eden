/* 
 * File:   Liquid.h
 * Author: Isaac
 *
 * Created on November 11, 2013, 5:03 PM
 */

#ifndef LIQUID_H
#define	LIQUID_H

#include "Fluid.h"

#include "../Gui/Draw.h"

struct LiquidAmt {
    LiquidType* liquid;
    kilogram amt;//kg
    kilogram deltaAmt;
    LiquidAmt(LiquidType* setLiquidType,kilogram setAmt) {
        liquid=setLiquidType;
        amt=setAmt;
        deltaAmt=0;
    }
    LiquidAmt(const LiquidAmt* orig) {
        liquid=orig->liquid;
        amt=orig->amt;
        deltaAmt=0;
    }
};
class Liquid : public Fluid
{
public:
    Liquid();
    virtual ~Liquid();
/*pure*/virtual Liquid* clone()const=0;
    void changeIntoLiquidAmt(LiquidAmt* become,Liquid* replace);
    //doing functions
    void checkForReplacement();
    virtual void preStep();
    virtual void update();
    virtual void endStep();
    void paint();
    virtual void draw();
    void drawFlow();
    virtual Color getColor()const{return *getLiquidType()->color;}
    virtual Color::hue colorAlpha()const;
    //info getters
    virtual void printInfo()const;
    inline bool submerged()const{return mass>0;}
    inline bool saturated()const{return saturatedMass>=getSaturation();}
    inline float height()const{return getVolume();}//area is assumed to be 1m^2
    float getVolume()const{return mass/getDensity();}
    bool freezing()const{return heat<=freezePoint();}
    bool changesVisible()const{return mass<1200;}
    //accessors
    inline kilogram mainLiquidMass()const{return mass+saturatedMass;}
    kilogram getTotalMass()const;
    kilogram saturationDiscrepancy()const;
    inline kilogram getDeltaMass()const{return deltaMass;}
    inline kilogram getNextMass()const{return mass+deltaMass;}
    inline const FluidVel* getDeltaVel()const{return deltaVel;}
    kilogram getSaturation()const;
    inline int containedAmt()const{return contained.size();}
    inline LiquidAmt* getContained(int l){return contained[l];}
    inline const LiquidAmt* getContained(int l)const{return contained[l];}
    //type-getters
/*pure*/virtual LiquidType* getLiquidType()const=0;
    inline float freezePoint()const{return getLiquidType()->freezePoint;}
    inline float boilPoint()const{return getLiquidType()->boilingPoint;}
    inline float getDensity()const{return getLiquidType()->density;}
    inline float flowRate()const{return getLiquidType()->flowRate;}
    inline float getSpecHeat()const{return getLiquidType()->specificHeat;}
    //mutators
    inline void setSaturatedMass(kilogram set){saturatedMass=set;}
    void setAndSatMass(kilogram set);
    void changeMass(kilogram amt);
    void giveVelocity(Dir* dir,kilogram amt);
    void giveMass(kilogram amt);
    void addAndSatMass(kilogram amt);
    void zeroMass();
    inline void setDeltaDroplets(kilogram set){deltaMass=set;}
    void giveLiquid(kilogram mass, LiquidType* type);
protected:
    void calcHeat();
    void runoff();
    void exchangeLiquid(Dir* dir);
    void flow();
    void sendLiquid(Dir* dir);
    void sendLiquid(Dir* dir,kilogram amt);
    void sendContained(Liquid* with,kilogram waterFlow);
    void haveTurbulence();
    void turbulence(Dir* dir);
    kilogram saturatedMass;
    kilogram deltaMass;
    FluidVel* deltaVel;
    vector<LiquidAmt*> contained;
};

#endif	/* LIQUID_H */

