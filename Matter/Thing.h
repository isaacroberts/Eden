/* 
 * File:   Thing.h
 * Author: Isaac
 *
 * Created on October 3, 2013, 11:33 PM
 */

#ifndef THING_H
#define	THING_H

#include <iostream>
#include <list>


#include "Matter.h"

class Square;

class Thing : public Matter
{
private:
    int id;
    static int curID;
    void assignID();
protected:
    byte references;//does not include refs from square
    //members
    Square* loc;
    //"constructor"
    void construct();
    //functions
    virtual void handlePhysics();
    virtual void calcHeat();
    virtual void handleFluidForces();
    virtual void update(){}
/*pure*/virtual void burn()=0;
    virtual void takePressure(double force,double area){}//newtons,m^2
    
    virtual void paintNormal();
    virtual void draw();
public:
    //doing functions
    Thing();
    Thing(float heat);
    Thing(const Thing& orig);
    virtual ~Thing();
    virtual void paint();
    virtual void preStep(){}
    void run();
    virtual void endStep(){}
    virtual void printInfo()const;
    virtual void getPushed(const FluidVel* vel,float massOfFluid);
    virtual void push(double force,Dir* dir){}//impulse- in newton seconds
    //setters
    virtual void setLoc(Square* set) {
        loc=set;    }
    //dimensionals
    virtual sizeval getSize()const=0;
    
    virtual float height()const=0;//meters
    virtual float surfaceArea()const=0;//square meters
    virtual float sideSurfaceArea()const{return height();}
    virtual float volume()const{return height();}
    virtual float getMass()const{return density()*volume();}
    virtual float density()const{return getType()->density;}
    inline float getDragCoefficient()const{return 1;}
    
    
    //reference functions
    void setRefs(byte set) {
        references=set;
    }
    void deleteRef();
    inline void addRef() {
        references++;
    }
    void banishFromSquare();
    
    
    //accessors
    virtual bool isDead()const;
    virtual Thing* clone()const;
    void makePropertiesSameAs(const Thing* orig);
/*pure*/virtual ThingType* getType()const=0;
    virtual bool isA(ThingType* type)const 
    {//allows extensions to still return true on their base type
        return type->equals(getType());
    }
    virtual bool isA(ThingType* type,ThingType* type2)const {
        if (type->equals(getType()))
            return true;
        else if (type2->equals(getType()))
            return true;
        else return false;
    }
    virtual Color getColor()const;
    virtual float getFlashPoint()const{return getType()->flashPoint;}
    virtual float getSpecHeat()const{return getType()->specificHeat;}
    
    inline bool burning()const {return heat>getFlashPoint() && !underwater();}
    bool underwater()const;
    inline Square* getLoc() const {
        return loc;
    }
    inline int getID() const {
        return id;
    }
    inline bool equals (const Thing* other) const {
        if (other==NULL) return false;
        return id==other->id;
    }
    inline bool operator ==(Thing* other)const {
        if (other==NULL) return false;
        return id==other->id;
    }
    inline bool isnt(const Thing* other) const {
        return id!=other->id;
    }
    //-abstract identifiers 
    inline virtual bool isNothing() {return false;}
    virtual bool isPlant() {return false;}
    virtual bool canMove()const{return false;}
    
/*-------------Static-----------*/
};
static inline bool areEqual(Thing* thing1,Thing* thing2)
{
    if (thing1==NULL)
        return false;
    if (thing2==NULL)
        return false;
    return thing1->getID()==thing2->getID();
}

#endif	/* THING_H */

