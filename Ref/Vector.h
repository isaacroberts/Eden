/* 
 * File:   Vector.h
 * Author: Isaac
 *
 * Created on October 11, 2013, 12:28 PM
 */

#ifndef VECTOR_H
#define	VECTOR_H

#include "Dir.h"


class Vector 
{
public:
    double xVel,yVel;
    Vector();
    Vector(double xVel,double yVel);
    Vector(const Vector& orig);
    virtual ~Vector(){}
    //mutators
    void setComponent(Dir* dir,double set);
    void addComponent(Dir* dir, double add);
    inline void set(const Vector* other){xVel=other->xVel;yVel=other->yVel;}
    inline void add(const Vector* other) {xVel+=other->xVel; yVel+=other->yVel; }
    inline void add(Vector other) {xVel+=other.xVel; yVel+=other.yVel; }
    inline void operator+=(Vector& other){xVel+=other.xVel; yVel+=other.yVel; }
    inline void multiply(double scale){xVel*=scale;yVel*=scale;}
    inline void operator*=(double scale){xVel*=scale;yVel*=scale;}
    void scaleTo(double magn);
    //other-vector-getters
    inline Vector sum(const Vector* other)const {
        return Vector(xVel+other->xVel,yVel+other->yVel); }
    inline Vector operator+(Vector& other){
        return Vector(xVel+other.xVel,yVel+other.yVel); }
    inline Vector product(double scale)const{return Vector(xVel*scale,yVel*scale);}
    inline Vector operator*(double scale)const{return Vector(xVel*scale,yVel*scale);}
    Vector getScaled(double scaleTo)const;
    double getComponentInDir(const Dir* mask)const;
    double getScalarComponentInDir(const Dir* mask)const;
    //accessors
    double magnitude()const;
    double sqrdMagnitude()const;
    double angle()const;//in radians
    inline bool isZero()const {return xVel==0 && yVel==0;}
    Dir* toDir()const;
    Dir* xDir()const;
    Dir* yDir()const;
    void printInfo()const;
    
    //static stuffz
    static Vector* zeroVector;
    static Vector getVector(const Square* from,const Square* to);
    static Vector getScaledVector(const Square* from,const Square* to,double scale);
    static Vector getSquareScaledVector(const Vector* orig,double scale);
    static Vector average(const Vector* v1,const Vector* v2,double weight1,double weight2);
private:
};

#endif	/* VECTOR_H */

