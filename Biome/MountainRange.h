/* 
 * File:   Mountains.h
 * Author: Isaac
 *
 * Created on November 15, 2013, 6:59 PM
 */

#ifndef MOUNTAINRANGE_H
#define	MOUNTAINRANGE_H
#include "Biome.h"
class MountainRange : public Biome
{
public:
    MountainRange();
    virtual float heat();
    virtual float humidity();
    virtual Terrain* getDefaultTerrain();
    virtual Liquid* getDefaultLiquid();
    virtual void setupWorld();
    virtual void genElevation();
    virtual void genTerrain();
    virtual void genLiquid();
    virtual void genOccupants();
    virtual ~MountainRange();
private:

};

#endif	/* MOUNTAINS_H */

