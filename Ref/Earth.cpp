
#ifndef EARTH_CPP
#define EARTH_CPP

#include <math.h>
//#include <iostream>
#include "Earth.h"

#include "Util.h"
#include "../Matter/Spring.h"
#include "../World/Square.h"
#include "../Gui/Gui.h"
long Spring::springFlow=7000;

namespace Earth
{
    //world
    const bool wraparound=true;
    const float TIME_STEP=1;
    const float gravity=.98;
    //sun/space
    float heatFromSun=.5;
    double heatLossToSpaceRatio=.0017241379;
    int timeOfDay=0,dayLength=100;
    float timeOfDaySunFactor;
    Color::hue nightAlpha=0;
    void setSunAndSpace(float intendedHeat, float sunHeat)
    {
        heatFromSun=sunHeat;
        heatLossToSpaceRatio=heatFromSun/intendedHeat;
        heatFromSun*=8;//i have no idea why this works
        
        heatFromSun*=.6666;// to cancel out day cycle
                    //trust me, i did the math
        cout<<"heatFromSun= "<<heatFromSun<<endl;
        cout<<"heatLossRatio= "<<heatLossToSpaceRatio<<endl;
    }
    void update()
    {
        timeOfDay++;
        if (timeOfDay>=dayLength)
            timeOfDay=0;
        timeOfDaySunFactor=sin(float(timeOfDay)/dayLength *6.28);
        Util::ensurePositive(timeOfDaySunFactor);
        
        int alpha=70-100*Earth::timeOfDaySunFactor;
        Util::ensurePositive(alpha);
        nightAlpha=alpha;
        if (nightAlpha>0 && nightAlpha<70)
        {
            if (nightAlpha%2==1)
                Gui::requireGlobalRedraw();
        }
    }
    //air
    const float airMass=10;//kg/m^2; air squares are 10 meters high
    const float airSpecHeat=1000;//J/kg
    const float airSpecificGasConstant=287.058;// Joules/(kg*Kelvin)
    //water
    //const long dropletsPerVolume=1000000;
    //one droplet is one gram of water
    float getEvaporation(float heat,float moisture,float surfaceArea,float humidity) {
        float evap;
        if (heat==0) {
            cout<<"heat = 0            wtfbro\n";
            return 0;
        }
        float vapPres=(float)pow(2.71,20.386-5132.0/heat);
        evap=(vapPres-humidity)/((float)sqrt(heat)) * surfaceArea;
        evap*=TIME_STEP;
//        evap/=waterDensity;
        if (evap>moisture)
            evap=moisture;
        if (-evap>humidity)
            evap=humidity;
        return evap;
    }   
}

#endif