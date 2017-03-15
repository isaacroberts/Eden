/* 
 * File:   Tree.cpp
 * Author: Isaac
 * 
 * Created on October 28, 2013, 2:48 PM
 */

#include "Tree.h"

#include "../World/Square.h"

#include "Plant.h"

#include "Fruit.h"
#include "Roots.h"

Tree::Tree() 
{
    Tree::construct();
    roots=new Roots(this);
    roots->addRef();
}
Tree::Tree(FruitType* setType)
{
    Tree::construct();
    fruitType=setType;
    roots=new Roots(this);
    roots->addRef();
}
Tree::Tree(FruitType* setFruitType, int setHeight)
{
    Tree::construct();
    length=setHeight;
    fruitType=setFruitType;
    roots=new Roots(this);
    roots->addRef();
    int rootLength=setHeight/500;
    Util::ensureBelow(rootLength,150);
    roots->setLength(rootLength);
}
Tree::Tree(FruitType* setFruitType, int setHeight,Roots* setRoots)
{
    Tree::construct();
    length=setHeight;
    fruitType=setFruitType;
    roots=setRoots;
    roots->addRef();
}
void Tree::construct()
{
    Plant::construct();
    length=300;
    fruitType=FruitType::Apple;
    fruitAmt=0;
}
Tree* Tree::clone() const
{
    Tree* copy=new Tree();
    copy->makePropertiesSameAs(this);
    copy->length=length;
    copy->setRoots(roots->clone());
    return copy;
}
Tree::~Tree() 
{
}
void Tree::setLoc(Square* set)
{
    loc=set;
    if (roots->getLoc()->notError())
        roots->getLoc()->removeOccupant(roots);
    loc->addOccupant(roots);
}
void Tree::printInfo()const
{
    Plant::printInfo();
    cout<<"   Fruit Type = "<<fruitType->name<<endl;
    cout<<"   Fruit Amount = "<<int(fruitAmt)<<endl;
}
bool Tree::canGrow() const {
    if (length<6000)
        return Util::everyNth(5,loc->getHash());
    else return false;
}
bool Tree::canReproduce() const {
    if (length>2000)
        return Util::everyNth(351,loc->getHash());
    else return false;
}
bool Tree::reproduce() {
    loc->requireRedraw();
    fruitAmt++;
    return true;
}
void Tree::update()
{
    if (canGrow())
        grow(1);
    if (canReproduce())
        reproduce();
    if (fruitAmt>0) 
    {
        int freq=250/fruitAmt;
        Util::ensureAbove(freq,1);
        if (Util::everyNth(freq,loc->getHash()))
        {
            if (requisitionWater(2))
            {
                fruitAmt--;
                Fruit* drop=new Fruit(fruitType);
                Dir* dir=Dir::getRandDir();
                Square* dropTo=loc->transform(dir);
                dropTo->addOccupant(drop);
                drop->accelerate(dir->x()/20.0,dir->y()/20.0);
//                cout<<"fruit dropped\n";
            }
        }
    }
    if (roots!=NULL)
    {
        if (roots->isDead())
        {
            roots->deleteRef();
            roots=NULL;
        }
        else if (Util::everyNth(125,loc->getHash()))
        {
            if (!roots->reproduce())
            {
                changeLength(-25);
            }
        }
    }
    else
    {
        changeLength(-25);
    }
}
void Tree::burn()
{ 
    changeLength(-4);
    heat+=2;
}
float Tree::getCalories() {
    return length*10;
}
void Tree::draw()
{
    if (burning())
    {
        Draw::setColor(burnColor());
        loc->fillCircle();
    }
    else
    {
        Draw::setColor(getType()->color,heightAlpha());
        loc->fillCircle();
        if (fruitAmt>0)
        {
            Draw::setColor(Color(fruitType->color,fruitAmt*50));
            Draw::circle(loc->px()+Square::halfSquareSize,loc->py()+Square::halfSquareSize
                    ,Square::quarterSquareSize);
        }
    }
}