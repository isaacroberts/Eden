/* 
 * File:   NoThing.h
 * Author: Isaac
 *
 * Created on October 4, 2013, 1:03 AM
 * 
 * 
 * Used only for Thing::none
 * so that squares dont have to check for null occupant before using occ
 * overrides all functions to do nothing
 */

#ifndef NOTHING_H
#define	NOTHING_H

#include "Thing.h"
using namespace std;

class NoThing : public Thing
{
public:
    NoThing() : Thing() {}
    NoThing(const NoThing& orig){}
    NoThing* clone() const{
        NoThing* noth=new NoThing();
        noth->makePropertiesSameAs(this);
        return noth;
    }
    virtual ~NoThing(){}
    Color getColor() {
        return Color();
    }
    ThingType* getType() const{
        return ThingType::None;
    }
    float height()const{return 0;}
    float surfaceArea()const {
        return 0;
    }
    sizeval getSize()const{return 0;}
    float sideSurfaceArea()const{return 0;}
    float volume()const{return 0;}
    float getMass()const{return 0;}
    float density()const{return 1000;}
    
    void paint() {}
    void printInfo()const{}
    void run(){}
    void handlePhysics(){}
    bool isSomething() {return false;}
    bool isNothing() {return true;}
protected:
    void update(){}
    void burn(){}
    void draw() {}

};

#endif	/* NOTHING_H */

