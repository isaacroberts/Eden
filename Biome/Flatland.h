/* 
 * File:   Flatland.h
 * Author: Isaac
 *
 * Created on November 15, 2013, 7:47 PM
 */

#ifndef FLATLAND_H
#define	FLATLAND_H
#include "Biome.h"
class Flatland : public Biome
{
public:
    Flatland();
    virtual float heat();
    virtual float humidity();
    virtual Terrain* getDefaultTerrain();
    virtual Liquid* getDefaultLiquid();
    virtual void setupWorld();
//    virtual void genElevation();
//    virtual void genTerrain();
//    virtual void genLiquid();
    virtual void genOccupants();
    virtual ~Flatland();
private:

};

#endif	/* FLATLAND_H */

