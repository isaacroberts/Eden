/* 
 * File:   FluidVel.cpp
 * Author: Isaac
 * 
 * Created on November 11, 2013, 11:37 AM
 */

#include "FluidVel.h"
#include "Vector.h"
#include <iostream>
FluidVel::FluidVel() 
{
    zero();
}
FluidVel::FluidVel(double n, double e, double s, double w)
{
    north=n;
    east=e;
    south=s;
    west=w;
}
FluidVel::FluidVel(const Vector* vec)
{
    if (vec->xVel>0)
    {
        east=vec->xVel;
        west=0;
    }
    else
    {
        west=-vec->xVel;
        east=0;
    }
    if (vec->yVel>0)
    {
        south=vec->yVel;
        north=0;
    }
    else 
    {
        north=-vec->yVel;
        south=0;
    }
}
FluidVel::FluidVel(double x, double y)
{
    if (x>0)
    {
        east=x;
        west=0;
    }
    else
    {
        west=-x;
        east=0;
    }
    if (y>0)
    {
        south=y;
        north=0;
    }
    else 
    {
        north=-y;
        south=0;
    }
}
FluidVel::FluidVel(const FluidVel& orig)
{
    north=orig.north;
    east=orig.east;
    west=orig.west;
    south=orig.south;
}
FluidVel::~FluidVel() {
}
//calc-changers
void FluidVel::add(const FluidVel* other)
{
    north+=other->north;
    south+=other->south;
    east+=other->east;
    west+=other->west;
}

void FluidVel::safeAdd(const FluidVel* other)
{
    north+=other->north;
    south+=other->south;
    east+=other->east;
    west+=other->west;
    if (north<0) {
        south-=north;
        north=0;
    }
    if (south<0) {
        north-=south;
        south=0;
    }
    if (west<0) {
        east-=west;
        west=0;
    }
    if (east<0) {
        west-=east;
        east=0;
    }
}
void FluidVel::add(const Vector* vec)
{
    if (vec->xVel>0)
        east+=vec->xVel;
    else
        west-=vec->yVel;
    if (vec->yVel>0)
        south+=vec->yVel;
    else 
        north-=vec->yVel;
}
void FluidVel::multiply(double factor)
{
    if (factor<0) {
        factor=-factor;
        flip();
    }
    north*=factor;
    south*=factor;
    east*=factor;
    west*=factor;
}
void FluidVel::reduce(double amt)
{
    north-=amt;
    west-=amt;
    east-=amt;
    south-=amt;
    Util::ensurePositive(north);
    Util::ensurePositive(west);
    Util::ensurePositive(east);
    Util::ensurePositive(south);
}
void FluidVel::flip() {
    int temp=north;
    north=south;
    south=temp;
    temp=east;
    east=west;
    west=temp;
}
void FluidVel::scaleTo(double magnitude)
{
    if (magnitude==0)
    {
        zero();
        return;
    }
    if (magnitude<0) {
        cout<<" Called FluidVel::scaleTo(magnitude="<<magnitude<<"); continuing and flipping FluidVel\n";
        flip();
        magnitude=-magnitude;
    }
    double largest=0;
    Util::ensureAbove(largest,south);
    Util::ensureAbove(largest,north);
    Util::ensureAbove(largest,east);
    Util::ensureAbove(largest,west);
    if (largest!=0)
    {    
        magnitude/=largest;
        north*=magnitude;
        south*=magnitude;
        east*=magnitude;
        west*=magnitude;
    }
}
//calculations
FluidVel FluidVel::sum(const FluidVel* other)const
{
    return FluidVel (north+other->north,east+other->east
            ,south+other->south,west+other->west);
}
FluidVel FluidVel::product(double factor) const
{
    if (factor<0)
    {
        factor=-factor;
        return FluidVel(south*factor,west*factor,
                north*factor,east*factor);
    }
    else
        return FluidVel (north*factor,east*factor,
            south*factor,west*factor);
}
FluidVel FluidVel::getScaled(double scaleTo) const
{
    if (scaleTo==0)
        return FluidVel();
    if (scaleTo<0) {
        cout<<" Called FluidVel::getScaled(scaleTo="<<scaleTo<<"); negative not accepted\n";
        return FluidVel();
    }
    double largest=0;
    Util::ensureAbove(largest,south);
    Util::ensureAbove(largest,north);
    Util::ensureAbove(largest,east);
    Util::ensureAbove(largest,west);
    if (largest==0)
        return FluidVel();
    scaleTo/=largest;
    return FluidVel (north*scaleTo,east*scaleTo,
            south*scaleTo,west*scaleTo);
}
FluidVel FluidVel::getFlipped() const
{
    return FluidVel(south,west,north,east);
}
//info-getters
double FluidVel::totalMovement()const
{
    return abs(east)+abs(north)+abs(south)+abs(west);
}
double FluidVel::summedMagnitude() const
{
    return sqrt(pow(xSum(),2)+pow(ySum(),2));
}
double FluidVel::sqrdSummedMagnitude() const
{
    return pow(xSum(),2)+pow(ySum(),2);
}
void FluidVel::change(Dir* dir, double amt)
{
    double& var=getVar(dir);
    var+=amt;
    Util::ensurePositive(var);
}
void FluidVel::printInfo() const
{
    printf("      N= %3f, S= %3f\n",north,south);
    printf("      E= %3f, W= %3f\n",east,west);
}
double& FluidVel::getVar(Dir* dir)
{
    if (dir->equals(Dir::East))
        return east;
    else if (dir->equals(Dir::North))
        return north;
    else if (dir->equals(Dir::South))
        return south;
    else if (dir->equals(Dir::West))
        return west;
    else {
        cout<<"FluidVel::getVar(Dir) called for "<<dir->toString()<<endl;
        return errorDoubleRef;
    }
}
double FluidVel::get(Dir* dir) const
{
    if (dir->equals(Dir::East))
        return east;
    else if (dir->equals(Dir::North))
        return north;
    else if (dir->equals(Dir::South))
        return south;
    else if (dir->equals(Dir::West))
        return west;
    else {
        cout<<"FluidVel::get(Dir) called for "<<dir->toString()<<endl;
        return -1;
    }
}
Dir* FluidVel::greatestDir()const
{
    Dir* greatest=Dir::North;
    double highest=north;
    if (south>highest) {
        greatest=Dir::South;
        highest=south;
    }
    if (east>highest) {
        greatest=Dir::East;
        highest=east;
    }
    if (west>highest) {
        greatest=Dir::West;
    }
    return greatest;
}
Dir* FluidVel::lowestDir()const
{
    Dir* least=Dir::North;
    double lowest=north;
    if (south<lowest) {
        least=Dir::South;
        lowest=south;
    }
    if (east<lowest) {
        least=Dir::East;
        lowest=east;
    }
    if (west<lowest) {
        least=Dir::West;
    }
    return least;
}
Dir* FluidVel::greatestMagnDir()const
{
    Dir* greatest=Dir::North;
    double highest=north;
    if (Util::greaterMagn(south,highest)) {
        greatest=Dir::South;
        highest=south;
    }
    if (Util::greaterMagn(east,highest)) {
        greatest=Dir::East;
        highest=east;
    }
    if (Util::greaterMagn(west,highest)) {
        greatest=Dir::West;
    }
    return greatest;
}
