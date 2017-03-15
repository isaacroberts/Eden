/* 
 * File:   Vector.cpp
 * Author: Isaac
 * 
 * Created on October 11, 2013, 12:28 PM
 */
#include <math.h>

#include "Vector.h"

#include "../World/Square.h"
#include "Util.h"
Vector* Vector::zeroVector=new Vector();

Vector::Vector() 
{
    xVel=yVel=0;
}
Vector::Vector(double setxVel,double setyVel) 
{
    xVel=setxVel;
    yVel=setyVel;
}
Vector::Vector(const Vector& orig)
{
    xVel=orig.xVel;
    yVel=orig.yVel;
}
double Vector::magnitude()const
{
    return sqrt(pow(xVel,2)+pow(yVel,2));
}
double Vector::sqrdMagnitude()const
{
    return pow(xVel,2)+pow(yVel,2);
}
double Vector::angle()const//in radians
{
    if (xVel==0)
    {
        if (yVel==0)
            return 0;
        return 1.5708;//pi/2
    }
    return atan2(yVel,xVel);//atan2 gives quadrant
}
Dir* Vector::toDir()const
{
    if (xVel==0 && yVel==0)
    {
        return Dir::Down;
    }
    else if (abs(xVel)>abs(yVel))
    {
        if (xVel>0)
            return Dir::East;
        else return Dir::West;
    }
    else
    {
        if (yVel>0)
            return Dir::South;
        else return Dir::North;
    }
}
Dir* Vector::xDir() const
{
    if (xVel==0) return Dir::Down;
    if (xVel>0)
        return Dir::East;
    else 
        return Dir::West;
}
Dir* Vector::yDir() const
{
    if (yVel==0) return Dir::Down;
    if (yVel>0)
        return Dir::South;
    else 
        return Dir::North;
}
void Vector::setComponent(Dir* dir, double set)
{
    if (dir->x()!=0)
    {
        if (dir->x()>0)
            xVel=set;
        else xVel=-set;
    }
    else
    {
        if (dir->y()>0)
            yVel=set;
        else yVel=-set;
    }
}
void Vector::addComponent(Dir* dir, double add)
{
    if (dir->x()!=0)
    {
        if (dir->x()<0)
            xVel-=add;
        else
            xVel+=add;
    }
    else
    {
        if (dir->y()<0)
            yVel-=add;
        else 
            yVel+=add;
    }
}
void Vector::scaleTo(double scaleTo)
{
    double factr=scaleTo/magnitude();
    xVel*=factr;
    yVel*=factr;
}
double Vector::getComponentInDir(const Dir* mask)const
{
    return xVel*mask->x()+yVel*mask->y();
}
double Vector::getScalarComponentInDir(const Dir* mask) const
{
    if (mask->x()==0)
    {
        double scalComp=yVel*mask->y();
        if (scalComp<=0)
            return 0;
        else return scalComp;
    }
    else
    {
        double scalComp=xVel*mask->x();
        if (scalComp<=0)
            return 0;
        else return scalComp;
    }
}
void Vector::printInfo() const
{
    cout<<"xVel="<<xVel<<", yVel="<<yVel;
}
Vector Vector::getScaled(double scale)const
{
    Vector ret=Vector(xVel,yVel);
    double factr=scale/magnitude();
    ret.xVel*=factr;
    ret.yVel*=factr;
    return ret;
}
//static shit
Vector Vector::getVector(const Square* from,const Square* to)
{
    return Vector(Util::xVectorComponent(from->x(),to->x()),from->y()-to->y());
}
Vector Vector::getScaledVector(const Square* from, const Square* to, double scale)
{
    if (scale==0) return Vector();
    Vector scaledVec= getVector(from,to);
    scaledVec.scaleTo(scale);
    return scaledVec;
}
Vector Vector::getSquareScaledVector(const Vector* orig, double scale)
{
    if (orig->isZero())
        return Vector();
    double factor;
    if (abs(orig->xVel)>abs(orig->yVel))
        factor=scale/abs(orig->xVel);
    else
        factor=scale/abs(orig->yVel);
    return orig->product(factor);
}
Vector Vector::average(const Vector* v1,const Vector* v2, double weight1, double weight2)
{
    if (weight1==0)
    {
        if (weight2==0)
            return Vector();
        else return Vector(*v2);
    } 
    else if (weight2==0)
        return Vector(*v1);
    Vector avg=Vector();
    avg.xVel=v1->xVel*weight1 + v2->xVel*weight2;
    avg.yVel=v1->yVel*weight1 + v2->yVel*weight2;
    avg.xVel/=weight1+weight2;
    avg.yVel/=weight1+weight2;
    return avg;
}