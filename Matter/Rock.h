/* 
 * File:   Rock.h
 * Author: Isaac
 *
 * Created on October 4, 2013, 11:51 AM
 */

#ifndef ROCK_H
#define	ROCK_H

#include "Thing.h"

using namespace std;

class Rock : public Thing
{
public:
    Rock()
    {
        construct();
    }
    virtual ~Rock(){}
    virtual ThingType* getType()const {
        return ThingType::Rock_T;
    }
    float height()const{return 2;}
    float surfaceArea()const {
        return 9;
    }
    sizeval getSize()const{return SizeVal::Huge;}
    float sideSurfaceArea()const{return 2;}
    virtual void update() {}
    virtual void burn() 
    {
//        loc->getTerrain()->changeHeat(1000);
//        loc->queueOccRemoval(this);
    }
    bool isAllocated()const{return true;}
private:

};

#endif	/* ROCK_H */

