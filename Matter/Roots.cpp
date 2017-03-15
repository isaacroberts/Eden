
#include "Roots.h"
#include "Tree.h"
#include "../World/Square.h"
#include "../main.h"

Roots::Roots() : Plant()
{
    parent=NULL;
    moisture=0;
}
Roots::Roots(Plant* setParent) : Plant()
{
    parent=setParent;
    parent->addRef();
    moisture=0;
}
Roots* Roots::clone() const
{
    Roots* copy=new Roots(parent);
    copy->length=length;
    copy->makePropertiesSameAs(this);
    copy->moisture=moisture;
    return copy;
}
Roots::~Roots()
{
    if (!Driver::ended)
    {
        if (parent)
           parent->deleteRef();
    }
}
void Roots::printInfo() const
{
    Plant::printInfo();
    cout<<"    Moisture : "<<moisture<<" kg\n";
    if (parent==NULL)
        cout<<"    Parent is NULL\n";
    else
        cout<<"    Parent is a "<<parent->getType()->toString()<<endl;
}
const float absorbRate=20;
const float flowRate=10;
void Roots::update()
{
    if (parent==NULL)
    {
        changeLength(-1);
    }
    else if (parent->isDead())
    {
        parent->deleteRef();
        parent=NULL;
        changeLength(-1);
    }
    else if (canGrow())
    {
        grow(1);
    }
    else
    {
        float liquid=loc->getLiquid()->getMass();
        if (moisture>0)
        {
            if (parent->isA(ThingType::Roots_T))
            {
                Util::trickle(moisture,((Roots*)parent)->moisture,flowRate);
                //send moisture from root to parent root
            }
            else if (parent->isA(ThingType::Tree_T))
            {
                Liquid* liq=getLoc()->getLiquid();
                if (!liq->saturated())
                {
                    float parentMoisture=liq->getMass();
                    Util::trickle(moisture,parentMoisture,flowRate);
                    liq->setMass(parentMoisture);
                }
            }
        }
        if (liquid>0)
        {
            Util::trickle(liquid,moisture,absorbRate);
        }   
    }
}
bool Roots::reproduce()
{
    if (canReproduce())
    {
        Square* growTo=loc->transform(Dir::getRandDir());
        if (growTo->notError())
        {
            Roots* inSquare=dynamic_cast<Roots*>(growTo->getOccOfType(ThingType::Roots_T));
            if (inSquare==NULL)
            {
                if (canGrowOn(growTo->getTerrain()->getType()))
                {
                    Roots* growth=new Roots(this);
                    growTo->addOccupant(growth);
                    return true;
                }
            }
            else if (equals(inSquare->getParent()))
            {
                return inSquare->reproduce();
            }
            else if (areEqual(inSquare->getParent(),parent)) 
            {
                return inSquare->reproduce();
            }
        }
    }
    return false;
}
int Roots::spawnDescendants(int amt)
{
    int reproductionAmt=0;
    length=150;//max roots length
    Dir* dir=Dir::getRandDir();
    for (int r=0;r<4 && reproductionAmt<amt;++r)
    {
        Square* growTo=loc->transform(dir);
        if (growTo->notError())
        {
            Roots* inSquare=dynamic_cast<Roots*>(growTo->getOccOfType(ThingType::Roots_T));
//            cout<<"    inSqr=  ";
            if (inSquare==NULL)
            {
//                cout<<"NULL\n";
                if (canGrowOn(growTo->getTerrain()->getType()))
                {
                    Roots* growth=new Roots(this);
                    growth->setLength(100);
                    growTo->addOccupant(growth);
                    reproductionAmt++;
                    if (reproductionAmt<amt) {
                        reproductionAmt+=growth->spawnDescendants(amt-reproductionAmt);
                    }
//                    cout<<"      grow\n";
                }
//                else cout<<"      cantgrow\n";
            }
//            else if (!areEqual(parent,inSquare) && isRelated(inSquare))
            else if (equals(inSquare->getParent()))
            {
//                cout<<inSquare->getID()<<endl;
//                cout<<"    recursive growth\n";
                reproductionAmt+= inSquare->spawnDescendants(amt-reproductionAmt);
            }
            else {
//                cout<<inSquare->getID()<<endl;
//                cout<<"   blocked\n";s
            }
        }
        dir=dir->rotateClockwise();
    }
//    cout<<"repr amt= "<<reproductionAmt<<" / "<<amt<<endl;
    return reproductionAmt;
}
bool Roots::forceReproduce()
{
    length=100;
    Dir* dir=Dir::getRandDir();
    for (int r=0;r<4;++r)
    {
        Square* growTo=loc->transform(dir);
        if (growTo->notError())
        {
            Roots* inSquare=dynamic_cast<Roots*>
                    (growTo->getOccOfType(ThingType::Roots_T));
            if (inSquare==NULL)
            {
                if (canGrowOn(growTo->getTerrain()->getType()))
                {
                    Roots* growth=new Roots(this);
                    growTo->addOccupant(growth);
                    growth->setLength(60);
                    return true;
                }
            }
            else if (equals(inSquare->getParent()))
            {//Warning: Do not change to isRelated.
                //It crashes the program from recursive stack overflow
//                cout<<"  Reproducing via relative\n";
                return inSquare->forceReproduce();
            }
        }
        dir=dir->rotateClockwise();
    }
    return false;
}
bool Roots::requisitionWater(float amt)
{
    if (moisture>=amt){
        moisture-=amt;
        return true;
    }
    else
    {
        amt-=moisture;
        moisture=0;
        return Plant::requisitionWater(amt);
    }
}
bool Roots::canGrowOn(TerrainType* type)const
{
    if (type->equals(ThingType::Grass_T))
        return true;
    if (type->equals(ThingType::Dirt_T))
        return true;
    if (type->equals(ThingType::Snow_T))
        return true;
    if (type->equals(ThingType::Sand_T))
        return true;
    return false;
}
void Roots::draw()
{
    Draw::setColor(getColor(),Color::colorBound(length*3));
    int px=loc->px(),py=loc->py();
    int sqr=Square::squareSize-1;
    Draw::line(px,py,px+sqr,py+sqr);
    Draw::line(px,py+sqr,px+sqr,py);
}
bool Roots::canGrow()const
{
    if (length<150)
        return true;
//        return Util::everyNth(61,loc->getHash());
    else return false;
}
bool Roots::canReproduce() const
{
    if (length>=100)
        return true;
//        return Util::everyNth(63,loc->getHash());
    else return false;
}
void Roots::burn()
{
    changeLength(-1);
    if (length%5==0)
        loc->requireRedraw();
    heat++;
}
