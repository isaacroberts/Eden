/* 
 * File:   Sky.h
 * Author: Isaac
 *
 * Created on October 18, 2013, 4:33 PM
 */

#ifndef SKY_H
#define	SKY_H

#include "Fluid.h"
#include "Terrain.h"

//class Square;
class Sky :public Fluid
{
public:
    //brahmin & shiva functions
    Sky();
    virtual ~Sky();
    //vishnu functions
    virtual void preStep();
    virtual void update();
    virtual void calcWind(Square* with,Dir* dir);
    virtual void diffuse(Sky* with);
    virtual void sendWind(Sky* to,Dir* dir,double blow);
    virtual void exchange(Square* with);
    virtual void endStep();
    virtual void paint();
    virtual void printInfo()const;
    //information getters
    
    inline float getVolume()const {return 1;}
    
    //accessors
    float getSpecHeat()const{return Earth::airSpecHeat;}
    inline float getHumidity()const{return humidity;}
    inline Square* getLoc() {return loc;}
    inline FluidVel* getWind(){return velocity;}
    //mutators
    void giveMass(float amt);
    void giveHeat(float amt);
    void giveWind(const Vector add);
    void giveHumidity(float amt);
    inline void setWind(FluidVel* set) {setVelocity(set);}
    inline void setHumidity(float set){humidity=set;}
    inline void changeHumidity(float amt) {humidity+=amt;
        Util::ensurePositive(humidity);   }
    bool takeMoisture(float amt);
protected:
    float humidity;//in kg of water
    float deltaHeat;
    float deltaMass;
    void drawHumidity();
    void drawHeat();
    void drawMass();
    void drawWind();
};

#endif	/* AIR_H */

