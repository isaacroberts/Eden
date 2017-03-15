/* 
 * File:   Pit.h
 * Author: Isaac
 *
 * Created on October 18, 2013, 8:31 PM
 */

#ifndef PIT_H
#define	PIT_H

#include "Terrain.h"
//#include "Water.h"

class Pit : public Terrain
{
    void update() {}
    void endStep() {
//        float siltLoss=
        loc->getLiquid()->setMass(0);
        Terrain::endStep();
    }
    virtual TerrainType* getType() const{
        return ThingType::Pit_T;
    }
    void paintNormal()
    {
        draw();
    }
    inline void paintWater()
    {
        if (displayType!=DisplayType::Normal)
            loc->getLiquid()->paint();
    }
    void checkMoisture() {}
    void burn(){}
};

#endif	/* PIT_H */

