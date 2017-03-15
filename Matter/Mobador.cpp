/* 
 * File:   Mobador.cpp
 * Author: Isaac
 * 
 * Created on November 22, 2013, 12:04 PM
 */

#include "Mobador.h"
#include "../World/Square.h"
#include "../main.h"

Mobador::Mobador() 
{
    velocity=new Vector();
    xPos=100;
    yPos=100;
}

Mobador::~Mobador() 
{
    delete velocity;
}
void Mobador::printInfo() const
{
    Thing::printInfo();
    cout<<"   Loc= ";
    loc->printString();
    cout<<endl;
    cout<<"   Velocity= ";
    velocity->printInfo();
    cout<<endl;
}
void Mobador::handlePhysics()
{
    Thing::handlePhysics();
    handleSliding();
    handleFluidForces();
    handleFriction();
}
void Mobador::handleSliding()
{
    float xSlope=0,ySlope=0;
    Terrain* terr=loc->getTerrain();
    xSlope=terr->getSlope(Dir::East)
            -terr->getSlope(Dir::West);
    ySlope=terr->getSlope(Dir::South)
            -terr->getSlope(Dir::North);
    slideDownhill(Dir::East,xSlope);
    slideDownhill(Dir::South,ySlope);
}
void Mobador::slideDownhill(Dir* dir,float slope)
{
    if (slope>=0) {
        return;
    }
    double accel=-Util::roughSinOfArcTan(slope);
    accel*=Earth::gravity;
    if (accel>0)
    {
        accelerate(dir,accel);
    }
}
float Mobador::getFrictionAccel() const
{
    return 9.8*loc->getTerrain()->getCoeffFriction();
    // a(f)=g*µ
}
void Mobador::handleFriction()
{
    float fric=getFrictionAccel();
    // ∆v= at ; t=1s
    //  a=F/m ; F=g*m*µ
    Util::reduceMagn(velocity->xVel,fric);
    Util::reduceMagn(velocity->yVel,fric);
}
void Mobador::preStep()
{
}
void Mobador::endStep()
{
    endStepMovement();
}
void Mobador::endStepMovement()
{
    if (velocity->isZero())
        return;
    //coord delta x/y
    int cDx=velocity->xVel*256;
    int cDy=velocity->yVel*256;
    if (cDx==0 && cDy==0 )
        return;
    Square* moveTo=loc->safeTranformCoord(xPos,yPos,cDx,cDy);
    if (loc->isnt(moveTo))
    {
        if (loc->getFreeSpace()>getSize())
        {
            GRID.queueThingMovement(this,moveTo);
            //collide with walls after finalizing movement
            if (moveTo->y()==0 && yPos<=5) 
            { //5 is some tolerance for hitting
                hitWalls();
            }
            else if ((moveTo->y()==(GRID.yAmt-1))
                    && (yPos<=COORD_RESOLUTION-5)) //5 tolerance
            {
                hitWalls();
            }
        }
        else
        {
            collide(loc->getBiggestOcc(),Dir::get(cDx,cDy));
        }
    }
}
void Mobador::push(double force, Dir* dir)
{
//    if (moved)
//        return false;
    if (force<=0)
    {
        return;
    }
    if (isDead()) {
        cout<<"Mobador dead on pushing\n";
//        setLoc(Square::squerror);
        return;
    }
    Square* toMove=loc->transform(dir);
    if (dir->equals(Dir::Down)) {
        cout<<" Error: a Mobador got pushed down"<<endl;
        return;
    }
    float slope=0;
    if (!toMove->isError()) {
        slope=loc->getTerrain()->getElevation()-toMove->getTerrain()->getElevation();
    }
//    if (toMove->y()==86) {
//        if (loc->y()!=87) {
//            cout<<" yVel = "<<velocity->yVel;
//            cout<<"   yPos="<<(int)yPos<<endl;
//        }
//    }
    float mass=getMass();
    float weight=mass*Earth::gravity;
    double extraForce=slope;
    extraForce*=weight;
    force+=extraForce;
    if (force>0) {
        force/=mass;
        accelerate(dir,force);
    }
}
void Mobador::move(Square* set)
{
    loc->removeOccupant(this);
    loc=set;
    loc->addOccupant(this);
}
void Mobador::collide(Thing* with,Dir* from)
{
    double speed=0;//its like force but technically correct
    if (from->x()==0)
    {
        speed=abs(velocity->yVel);
        velocity->yVel=0;
    }
    else if (from->y()==0)
    {
        speed=abs(velocity->xVel);
        velocity->xVel=0;
    }
    
    
}
void Mobador::hitWalls()
{
    velocity->yVel=-velocity->yVel;
}
 