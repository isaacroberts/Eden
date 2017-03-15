/* 
 * File:   Forest.h
 * Author: Isaac
 *
 * Created on November 15, 2013, 5:29 PM
 */

#ifndef FOREST_H
#define	FOREST_H

#include "Biome.h"

class Forest : public Biome
{
public:
    Forest();
    virtual float heat();
    virtual float humidity();
    virtual Terrain* getDefaultTerrain();
    virtual Liquid* getDefaultLiquid();
    virtual void setupWorld();
    virtual void genElevation();
    virtual void genTerrain();
    virtual void genLiquid();
    virtual void genOccupants();
    virtual ~Forest();
private:

};

#endif	/* FOREST_H */

