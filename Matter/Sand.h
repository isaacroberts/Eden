/* 
 * File:   Sand.h
 * Author: Isaac
 *
 * Created on October 28, 2013, 12:41 PM
 */

#ifndef SAND_H
#define	SAND_H

#include "Terrain.h"
#include "Glass.h"
#include "../World/Square.h"

class Sand : public Terrain
{
    public:
    Sand() {
        construct();
    }
    virtual TerrainType* getType() const{
        return ThingType::Sand_T;
    }
    virtual ~Sand() 
    {
    }
protected:
    void update(){}
    void burn()
    {
        loc->queueTerrainReplacement(new Glass());
    }
};

#endif	/* SAND_H */

