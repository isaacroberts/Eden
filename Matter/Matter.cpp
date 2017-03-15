/* 
 * File:   Shoehorn.cpp
 * Author: Isaac
 * 
 * Created on November 18, 2013, 12:44 PM
 */

#include "Matter.h"

Matter::Matter() {
}

Matter::Matter(const Matter& orig) {
}

Matter::~Matter() {
}
void Matter::exchangeHeat(Matter* with,float rate,float contactArea)
{
    float ownHeatMass=heatMass();
    float otherHeatMass=with->heatMass();
    if (ownHeatMass<1) {
        if (otherHeatMass<1) {
            if (otherHeatMass<ownHeatMass) {
                ownHeatMass/=otherHeatMass;
                otherHeatMass=1;
            }
            else {
                otherHeatMass/=ownHeatMass;
                ownHeatMass=1;
            }
            rate=.5;
        }
        else {
            setHeat(with->getHeat());
            return;
        }
    }
    else if (otherHeatMass<1) {
        with->setHeat(heat);
        return;
    }
    else
    {
        Util::ensureBelow(rate,ownHeatMass/2);
        Util::ensureBelow(rate,otherHeatMass/2);
    }
    float deltaHeat=(heat-with->getHeat());
    if (deltaHeat<.5 && deltaHeat>-.5) return;
    deltaHeat*=rate;
    changeHeat(-deltaHeat/ownHeatMass);
    with->changeHeat(deltaHeat/otherHeatMass);
    
}