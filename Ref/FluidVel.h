/* 
 * File:   FluidVel.h
 * Author: Isaac
 *
 * Created on November 11, 2013, 11:37 AM
 */

#ifndef FLUIDVEL_H
#define	FLUIDVEL_H

#include "Util.h"
#include "Dir.h"

#include "Vector.h"

class FluidVel {
public:
    FluidVel();
    FluidVel(const Vector*);
    FluidVel(double n,double e,double s,double w);
    FluidVel(double x,double y);
    FluidVel(const FluidVel& orig);
    inline FluidVel* clone()const {
        return new FluidVel(north,east,south,west);
    }
    virtual ~FluidVel();
    
    //changers
    inline void zero(){south=east=west=north=0;}
    void add(const FluidVel* other);
    void safeAdd(const FluidVel* other);
    void add(const Vector* toAdd);
    void reduce(double amt);
    void multiply(double factor);
    void scaleTo(double magnitude);
    void flip();
    //vector-style calculations
    FluidVel sum(const FluidVel* other)const;
    FluidVel product(double multiplyBy)const;
    FluidVel getScaled(double scaleTo)const; 
    FluidVel getFlipped()const;
    //info getters
    void printInfo()const;
    inline Vector toVector()const{return Vector(xSum(),ySum());}
    inline double xSum()const{return east-west;}
    inline double ySum()const{return south-north;}
    double totalMovement()const;
    double summedMagnitude()const;
    double sqrdSummedMagnitude()const;
    inline bool isZero()const{return east==0&&west==0&&north==0&&south==0;}
    inline bool notZero()const{return east!=0||west!=0||north!=0||south!=0;}
    Dir* greatestDir()const;
    Dir* lowestDir()const;
    Dir* greatestMagnDir()const;
    //accessors
    double get(Dir* dir) const;
    inline double getEast()const{return east;}
    inline double getWest()const{return west;}
    inline double getNorth()const{return north;}
    inline double getSouth()const{return south;}
    //mutators
    inline void set(Dir* dir,double set){getVar(dir)=set;}
    inline void setEast(double set){east=set;}
    inline void setWest(double set){west=set;}
    inline void setNorth(double set){north=set;}
    inline void setSouth(double set){south=set;}
    
    void change(Dir* dir,double amt);
    inline void changeWest(double amt){west+=amt;Util::ensurePositive(west);}
    inline void changeNorth(double amt){north+=amt;Util::ensurePositive(north);}
    inline void changeEast(double amt){east+=amt;Util::ensurePositive(east);}
    inline void changeSouth(double amt){south+=amt;Util::ensurePositive(south);}
    
    inline void unsafeChange(Dir* dir,double amt){getVar(dir)+=amt;}
private:
    double east,south,north,west;
    double& getVar(Dir* dir);
};

#endif	/* FLUIDVEL_H */

