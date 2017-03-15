/* 
 * File:   Snow.h
 * Author: Isaac
 *
 * Created on November 3, 2013, 6:40 PM
 */

#ifndef SNOW_H
#define	SNOW_H

#include "Covering.h"

class Snow : public Covering
{
public:
    Snow();
    Snow(TerrainType* setUnder);
    Snow(Terrain* orig);
    void construct();
    void replace(Terrain* other,float depth);
    void freeze(Terrain* toFreeze);
    Snow* clone()const;
    virtual ~Snow();
    TerrainType* getType() const {
        return ThingType::Snow_T;
    }
    void erode(float amt);
    virtual void printInfo()const;
    void draw();
    inline void setDepth(float set) {depth=set;}
    inline float getDepth() {return depth;}
protected:
     void update();
     void meltAndFreeze();
     void burn() {}
private:
    float depth;
};

#endif	/* SNOW_H */

