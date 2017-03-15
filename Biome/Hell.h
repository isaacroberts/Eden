/* 
 * File:   Hell.h
 * Author: Isaac
 *
 * Created on November 15, 2013, 7:15 PM
 */

#ifndef HELL_H
#define	HELL_H
#include "Biome.h"
class Hell : public Biome
{
public:
    Hell();
    virtual float heat();
    virtual float humidity();
    virtual Terrain* getDefaultTerrain();
    virtual Liquid* getDefaultLiquid();
    virtual void setupWorld();
    virtual void genElevation();
    virtual void genTerrain();
    virtual void genLiquid();
    virtual void genOccupants();
    virtual ~Hell();
private:

};

#endif	/* HELL_H */

