/* 
 * File:   Desert.h
 * Author: Isaac
 *
 * Created on November 15, 2013, 6:28 PM
 */

#ifndef DESERT_H
#define	DESERT_H
#include "Biome.h"

class Desert : public Biome
{
public:
    Desert();
    virtual float heat();
    virtual float humidity();
    virtual Terrain* getDefaultTerrain();
    virtual Liquid* getDefaultLiquid();
    virtual void setupWorld();
    virtual void genElevation();
    virtual void genTerrain();
    virtual void genLiquid();
    virtual void genOccupants();
    virtual ~Desert();
private:

};

#endif	/* DESERT_H */

