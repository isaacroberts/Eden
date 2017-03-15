/* 
 * File:   Bedrock.h
 * Author: Isaac
 *
 * Created on November 15, 2013, 4:45 PM
 */

#ifndef GRANITE_H
#define	GRANITE_H

#include "Terrain.h"

class Granite : public Terrain
{
    public:
    Granite() : Terrain() {
    }
    TerrainType* getType()const{
        return ThingType::Granite_T;
    }
    Granite* clone()const{
        Granite* copy=new Granite();
        copy->makePropertiesSameAs(this);
        return copy;
    }
    void burn(){}
    
};

#endif	/* BEDROCK_H */

