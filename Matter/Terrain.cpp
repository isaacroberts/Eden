/* 
 * File:   Terrain.cpp
 * Author: Isaac
 * 
 * Created on October 4, 2013, 1:08 PM
 */

#include "Terrain.h"
#include "../_.h"

Terrain::Terrain()
{
    Terrain::construct();
}
void Terrain::construct()
{
    Thing::construct();
    elevation=0;
}
Terrain* Terrain::clone() const
{
    Terrain* copy=getType()->getInstance();
    copy->makePropertiesSameAs(this);
    return copy;
}
void Terrain::replace(Terrain* replacing)
{
    if (replacing==NULL)
    {
        cout<<"Terrain::replace called with NULL parameter?\n";
//        exit(1);
    }
    else
    {
        loc=replacing->loc;
        heat=replacing->heat;
        elevation=replacing->elevation;
    }
}
void Terrain::makePropertiesSameAs(const Terrain* copy)
{
    Thing::makePropertiesSameAs(copy);
    elevation=copy->elevation;
}
Terrain::~Terrain() 
{
}
void Terrain::preStep()
{
}
void Terrain::handlePhysics()
{
    calcHeat();
//    handleErosion();
    checkForBurn();
}
void Terrain::handleErosion()
{
    if (loc->getLiquid()->submerged() 
            && loc->getLiquid()->getVelocity()->notZero())
    {
        Dir* dir=Dir::North;
        for (int n=0;n<4;++n)
        {
            double vel=loc->getLiquid()->getVelocity()->get(dir);
            if (vel>0)
            {
                
            }
            dir=dir->rotateClockwise();
        }
    }
}
void Terrain::checkForBurn()
{
    if (burning() && !underwater())
        burn();
}
void Terrain::endStep()
{
    heat*=1-Earth::heatLossToSpaceRatio;
    heat+=Earth::getHeatFromSun() * getSunReceptivity();
}
void Terrain::calcHeat()
{
    //when the rate is above or close to .5,
    // heat travels west and leaves a trail moving north
    exchangeHeat(loc->transform(Dir::West),100);
    exchangeHeat(loc->transform(Dir::North),100);
}
void Terrain::exchangeHeat(Square* with, float rate)
{//rate must be less than one and greater than zero
    if (with->isError())
        return;
    Matter::exchangeHeat(with->getTerrain(),rate,5);
                //assuming 5m down of terrain matters
}
//graphics functions
void Terrain::paint()
{
    if (displayType==DisplayType::Normal)
    {
        paintNormal();
    }
    else if (displayType==DisplayType::Elevation)
    {
        drawElevation();
    }
}
void Terrain::paintNormal()
{
    if (loc->getLiquid()->colorAlpha()<254)
    {
        draw();
        if (elevation>0)
            Draw::setColor(Color::WHITE,Color::colorBound(elevation*elevationDrawSlope));
        else
            Draw::setColor(Color::BLACK,Color::colorBound(-elevation*elevationDrawSlope));
        loc->fillRect();
    }
}
void Terrain::draw()
{
    Draw::setColor(getColor());
    loc->fillRect();
}
void Terrain::drawElevation()
{
    float elev;
    elev=abs(elevation-loc->transform(Dir::East)->getTerrain()->getElevation());
    if (loc->y()>0)
        Util::ensureAbove(elev,abs(elevation-loc->transform(Dir::North)->getTerrain()->getElevation()));
//    else elev*=2;
    
    elev*=200;
    if (elev>255)
    {
        Draw::setColor(Color::makeColor(255,511-elev,511-elev));
    }
    else
    {
        Color::hue gray=Color::colorBound((elev));
        Draw::setColor(gray,gray,gray);
    }
    loc->fillRect();
}
void Terrain::drawHeat()
{
    Color::hue r=Color::colorBound((heat-230.15)*2);
    Draw::setColor(Color::makeColor(r,0,255-r));
    loc->fillRect();
}
//setters
void Terrain::setLoc(Square* set)
{
    loc=set;
}
//accessors
void Terrain::printInfo()const
{
    cout<<"  "<<getType()->toString()<<":"<<endl;
    cout<<"    Heat= "<<heat<<endl;
    cout<<"    Elevation= "<<elevation<<endl;
}
bool Terrain::underwater() const
{
    return loc->getLiquid()->height()>1;
}
long Terrain::waterAbove()const
{
    return loc->getLiquid()->getMass();
}
float Terrain::metersOfWaterAbove() const
{
    return loc->getLiquid()->height();
}
float Terrain::altitude() const
{
    return metersOfWaterAbove()+getElevation();
}
kilogram Terrain::saturation() const
{
    return getType()->saturation;
}
float Terrain::getCoeffFriction() const
{
    return getType()->friction;
}
float Terrain::getSunReceptivity() const
{
    if (underwater())
    {
        return loc->getLiquid()->getLiquidType()->sunReceptivity;
    }
    else return getType()->sunReceptivity;
}
float Terrain::getSlope(Dir* dir) const
{
    Terrain* nayb=loc->transform(dir)->getTerrain();
    if (nayb==NULL)
        return 0;
    return nayb->getElevation()-elevation;
}