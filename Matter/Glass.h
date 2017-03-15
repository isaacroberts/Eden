/* 
 * File:   Glass.h
 * Author: Isaac
 *
 * Created on October 29, 2013, 10:18 AM
 */

#ifndef GLASS_H
#define	GLASS_H

#include "Terrain.h"

class Glass : public Terrain
{
public:
    Glass() : Terrain()
    {
        construct();
    }
    virtual TerrainType* getType() const {
        return ThingType::Glass_T;
    }
    virtual Glass* clone() const
    {
        Glass* copy=new Glass();
        copy->makePropertiesSameAs(this);
        return copy;
    }
    virtual ~Glass() {}
protected:
    void burn() {}
private:

};

#endif	/* GLASS_H */

