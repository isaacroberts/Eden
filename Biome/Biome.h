/* 
 * File:   Biome.h
 * Author: Isaac
 *
 * Created on November 15, 2013, 5:24 PM
 */

#ifndef BIOME_H
#define	BIOME_H

class Terrain;
class Liquid;
class Square;

class Biome {
public:
    Biome() {}
    virtual float heat()=0;
    virtual float humidity()=0;
    virtual Terrain* getDefaultTerrain()=0;
    virtual Liquid* getDefaultLiquid()=0;
    virtual void setupWorld(){}
    virtual void genElevation(){}
    virtual void genTerrain(){}
    virtual void genLiquid(){}
    virtual void genOccupants(){}
    virtual ~Biome(){}
private:

};

#endif	/* BIOME_H */

