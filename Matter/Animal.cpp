/* 
 * File:   Animal.cpp
 * Author: Isaac
 * 
 * Created on February 19, 2014, 12:44 PM
 */

#include "Animal.h"

#include "../Gui/Draw.h"
#include "../World/Square.h"

#include "Fruit.h"
/*--------Construction & Destruction---------*/
Animal::Animal(Species* setSpecies) 
{
    species=setSpecies;
    blood=species->getMaxBlood()/2;
    energy=species->getMaxEnergy();
}
Animal::Animal(const Animal& orig) 
{
    cout<<"attemping to copy an animal;"
            " dont you know theyre drm protected?"<<endl;
    exit(0);
}
Animal::~Animal() 
{   
}
/*-------Doing Functions--------------*/
void Animal::preStep()
{
    loc->requireRedraw();
}
void Animal::update()
{
    metabolize();
    Thing* fruit= loc->getOccOfType(ThingType::Fruit_T);
    if (fruit!=NULL)
    {
        Fruit* food=dynamic_cast<Fruit*>(fruit);
        digest(food->getAte());
    }
}
void Animal::burn()
{
    
}
/*---------Animally things----------------*/
void Animal::hit(double force, double area)
{
    
}
void Animal::metabolize()
{
    energy-=species->getMetabolism();
    if (energy<=0)
    {
        energy=0;
        blood-=.01;
        Util::ensurePositive(blood);
    }
    else
    {
        blood+=species->getBloodRegen();
        Util::ensureBelow(blood,species->getMaxBlood());       
    }
}
void Animal::digest(float energyEaten)
{
    energy+=energyEaten;
    long excessEnergy=energy-species->getMaxEnergy();
    if (excessEnergy>0)
    {
        energy-=excessEnergy;
        addHeatEnergy(excessEnergy);
    }
}
void Animal::endStep()
{
    endStepMovement();
}
void Animal::draw()
{
    Draw::setColor(getColor());
    loc->fillCircle();
    drawStatusBars();
}
void Animal::drawStatusBars()
{
    int barHeit=Util::roundUp(Square::squareSize*.1);
    int gap=barHeit*1.5;
    
    Draw::setColor(150,0,0);
    int drawWidth=blood/species->getMaxBlood() * Square::squareSize;
    Draw::rect(loc->px(),loc->py(),drawWidth-1,barHeit);
    
    Draw::setColor(0,200,0);
    drawWidth=energy/species->getMaxEnergy() * Square::squareSize;
    Draw::rect(loc->px(),loc->py()+gap,drawWidth-1,barHeit);
    
    int linePt=Square::squareSize/15;
    if (linePt>0)
    {
        Draw::setColor(Color::BLACK);
        Draw::traceRect(loc->px(),loc->py(),Square::squareSize-1,barHeit,linePt);
        Draw::traceRect(loc->px(),loc->py()+gap,Square::squareSize-1,barHeit,linePt);
    }
}
/*----Info & Nonvariable Access-------------*/
void Animal::printInfo()const
{
    Mobador::printInfo();
//    cout<<"   Species = "<<species->getName()<<endl;
    cout<<"   Blood = "<<blood<<endl;
    cout<<"   Energy= "<<energy<<endl;
}
bool Animal::isDead()const
{
    return loc->isError() || blood<=0;
}
float Animal::height() const
{
    return 1;
}
float Animal::surfaceArea() const
{
    return 4;
}