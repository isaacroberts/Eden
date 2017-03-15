/* 
 * File:   Earth.h
 * Author: Isaac
 *
 * Created on October 7, 2013, 4:01 PM
 */

#ifndef EARTH_H
#define	EARTH_H

#include "../Gui/Color.h"

namespace Earth
{
    extern const bool wraparound;
    extern const float TIME_STEP;
    extern const float gravity;
    //sun/space
    extern float heatFromSun;
    extern double heatLossToSpaceRatio;
    extern int timeOfDay,dayLength;
    extern float timeOfDaySunFactor;
    extern Color::hue nightAlpha;
    void setSunAndSpace(float intendedHeat,float sunHeat);
    void update();
    inline float getHeatFromSun() {
        return heatFromSun*timeOfDaySunFactor;
    }
    //air
    extern const float airMass;
    extern const float airSpecHeat;
    extern const float airSpecificGasConstant;
    
    //water
    float getEvaporation(float heat,float moisture,float surfaceArea,float humidity);
    
}
#endif	/* EARTH_H */

