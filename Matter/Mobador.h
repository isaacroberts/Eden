/* 
 * File:   Mobador.h
 * Author: Isaac
 *
 * Created on November 22, 2013, 12:04 PM
 */

#ifndef MOBADOR_H
#define	MOBADOR_H

#include "Thing.h"

class Mobador : public virtual Thing
{
public:
    
    Mobador();
    virtual void preStep();
    virtual void endStep();
    virtual void endStepMovement();
    virtual void push(double force,Dir* dir);//impulse- in newton seconds
    void move(Square*);
    virtual void hitWalls();
    inline void accelerate(Dir* dir, double accel) {
        velocity->addComponent(dir,accel);
    }
    inline void accelerate(double dx,double dy) {
        velocity->xVel+=dx;
        velocity->yVel+=dy;
    }
    inline void actUnderForce(Dir* dir,double force) {
        accelerate(dir,force/getMass());
    }
    virtual void collide(Thing* with,Dir* from);
//    virtual void collide(Thing* with){}
    virtual void hit(double force,double area){}//newtons, m^2
    virtual void hit(double force){}//assumed SA=this.surfaceArea
    
    virtual float getFrictionAccel()const;
    inline float getWeight()const{return getMass()*Earth::gravity;}
    virtual ~Mobador(); 
    bool canMove()const{return true;}
//    bool hasMoved()const{return moved;}
    
    bool isAllocated()const{return true;}
    virtual void printInfo()const;
protected:
    virtual void handlePhysics();
    void handleSliding();
    virtual void handleFriction();
    void slideDownhill(Dir*,float slope);
    Vector* velocity;//in m/s
    coord xPos,yPos;//1 coord = m/256
    
};

#endif	/* MOBADOR_H */

