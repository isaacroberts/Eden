/* 
 * File:   Snow.h
 * Author: Isaac
 *
 * Created on November 3, 2013, 6:37 PM
 */

#ifndef COVERING_H
#define	COVERING_H

#include "Terrain.h"

class Covering : public Terrain
{
public:
    Covering();
    Covering(Terrain* orig);
    virtual void replace(Terrain* other);
    void construct();
    virtual ~Covering();
    virtual void printInfo()const;
    TerrainType* getTypeUnder() {return under;}
    void changeWhatsUnder(TerrainType* set){under=set;}
    bool isCovering(){return true;}
protected:
    TerrainType* under;
private:
};

#endif	/* SNOW_H */

