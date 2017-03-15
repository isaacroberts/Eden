/* 
 * File:   Liquid.cpp
 * Author: Isaac
 * 
 * Created on November 11, 2013, 5:03 PM
 */

#include "Liquid.h"
#include "Terrain.h"
#include "../World/Square.h"

Liquid::Liquid() : Fluid(), contained(vector<LiquidAmt*>())
{
    deltaMass=0;
    deltaVel=new FluidVel();
    saturatedMass=0;
}
Liquid::~Liquid() 
{
    for (int l=0;l<contained.size();++l)
        delete contained[l];
    delete deltaVel;
}
void Liquid::changeIntoLiquidAmt(LiquidAmt* become, Liquid* replace)
{
    mass=become->amt;
    saturatedMass=replace->saturatedMass;
    contained=vector<LiquidAmt*>();
    LiquidAmt* prevMain=new LiquidAmt(replace->getLiquidType(),replace->getMass());
    prevMain->deltaAmt=replace->getDeltaMass();
    contained.push_back(prevMain);
    
    for (int l=0;l<replace->containedAmt();++l)
    {
        LiquidAmt* add=replace->getContained(l);
        if (add->liquid!=getLiquidType())
            contained.push_back(new LiquidAmt(add));
    }
    delete velocity;
    velocity=replace->getVelocity()->clone();
}
static const kilogram seepRate=50;
void Liquid::preStep()
{
    if (mass>.01)
    {
        //slowly seep liquid into the ground until saturation
        kilogram satDiscrep=saturationDiscrepancy();
        
        if (abs(satDiscrep)>seepRate)
        {
            if (satDiscrep>0)
                Util::trickle(mass,saturatedMass,seepRate);
            else
                Util::trickle(saturatedMass,mass,seepRate);
        }
        else if (satDiscrep!=0) 
        {
            Util::trickle(mass,saturatedMass,satDiscrep);
        }
        if (mass < 100 )// if changes will be Visible
            loc->requireRedraw();
        velocity->multiply(.4);
        runoff();
    }
    else
    {
        velocity->zero();
    }
    checkForReplacement();
}
void Liquid::checkForReplacement()
{
    kilogram mainMass=mass;
    LiquidAmt* mostLiquid=NULL;
    for (int l=0;l<contained.size();++l)
    {
        if (contained[l]->amt>mainMass)
        {
            if (mostLiquid==NULL || 
                    mostLiquid->amt<contained[l]->amt)
            {
                mostLiquid=contained[l];
            }
        }
    }
    if (mostLiquid!=NULL)
    {
        Liquid* replacement=mostLiquid->liquid->getInstance();
        replacement->changeIntoLiquidAmt(mostLiquid,this);
        loc->replaceLiquid(replacement);
    }
}
void Liquid::update()
{
    if (!submerged()) return;
    flow();
//    haveTurbulence();
    calcHeat();
}
void Liquid::endStep()
{
    velocity->safeAdd(deltaVel);
    deltaVel->zero();
    mass+=deltaMass;
    if (abs(deltaMass)>2)
    {
        if (abs(deltaMass)>100 || changesVisible())
            loc->requireRedraw();
    }
    deltaMass=0;
    Util::ensurePositive(mass);
    for (int l=0;l<contained.size();++l) {
        contained[l]->amt+=contained[l]->deltaAmt;
        contained[l]->deltaAmt=0;
        Util::ensurePositive(contained[l]->amt);
    }
}
void Liquid::printInfo() const
{
    cout<<"  "<<getLiquidType()->toString()<<":\n";
    Fluid::printInfo();
    cout<<"    Saturation Mass = "<<saturatedMass<<endl;   
    cout<<"      Terrain Saturation = "<<getSaturation()<<endl;
    if (!contained.empty())
    {
        cout<<"    Contains : "<<endl;
        for (int l=0;l<contained.size();++l)
        {
            if (contained[l]->amt!=0)
                cout<<"       "<<contained[l]->liquid->toString()
                        <<"  : "<<contained[l]->amt<<endl;
        }
    }
}
void Liquid::calcHeat()
{
    exchangeHeat(loc->getTerrain(),100,loc->getTerrain()->surfaceArea());
}
void Liquid::haveTurbulence()
{
}
void Liquid::runoff()
{
    if (mass<50) return;
    exchangeLiquid((Dir::South));
    exchangeLiquid((Dir::East));
    exchangeLiquid((Dir::West));
    exchangeLiquid((Dir::North));
}
void Liquid::exchangeLiquid(Dir* dir)
{
    Square* with=loc->transform(dir);
    if (with->isError()) return;
    float levelDiff=(loc->getTerrain()->altitude()
            - with->getTerrain()->altitude());
    float flow=levelDiff/5;
    
    kilogram massFlow=flow*getDensity();
    Util::ensureBelow(massFlow,mass/8);
    velocity->change(dir,massFlow);
}
void Liquid::flow()
{
    if (mass<1) return;
    sendLiquid(Dir::North);
    sendLiquid(Dir::South);
    sendLiquid(Dir::East);
    sendLiquid(Dir::West);
}
void Liquid::sendLiquid(Dir* dir)
{
    if (loc->transform(dir)->isError()) return;
    kilogram flow=velocity->get(dir);
    if (flow>1) 
    {//must be positive; >1 prevents floating point errors
        if (flow>mass) {
            flow=mass;
            velocity->set(dir,flow);
        }
        sendLiquid(dir,flow);
    }
}
void Liquid::sendLiquid(Dir* dir,kilogram flow)
{
    Square* sendTo=loc->transform(dir);
    if (sendTo->isError()) return;
    if (flow>mass) {
        flow=mass;
    }
    flow*=flowRate();
    if (flow<=0)
        return;
    Liquid* with=sendTo->getLiquid();
    //send velocity
    kilogram velSend=velocity->get(dir)*flow;
    velSend/=flow+with->mass;
    velSend/=1.4;
    with->giveVelocity(dir,velSend);
    //exchange heat
    float otherHeat=with->getHeat();
    float avgHeat=Util::avg(heat,mass,otherHeat,with->getMass());
    avgHeat-=with->getHeat();
    with->giveHeat(avgHeat);
    //transfer mass
    giveMass(-flow);
    with->giveLiquid(flow,getLiquidType());
    
    sendContained(with,flow);
}
void Liquid::sendContained(Liquid* with, kilogram flow)
{
    if (flow<0) return;
    float flowRatio=flow/mass;
    for (int l=0;l<contained.size();++l)
    {
        kilogram delta=flowRatio*contained[l]->amt;
        contained[l]->amt-=delta;
        with->giveLiquid(delta,contained[l]->liquid);
    }
}
void Liquid::paint()
{
    if (displayType==DisplayType::Normal)
    {
        if (!loc->getTerrain()->isA(TerrainType::Spring_T,TerrainType::Pit_T))
            draw();
    }
    else if (displayType==DisplayType::WaterFlow)
    {
        drawFlow();
    }
}
void Liquid::draw()
{
    if (mass<0) {
        Draw::setColor(0,255,0);
        loc->fillRect();
    }
    else
    {
        Color color=getColor();
        kilogram totalMass=mass;
        for (int l=0;l<contained.size();++l)
        {
            color=color.avg(contained[l]->liquid->color,
                    totalMass,contained[l]->amt);
            totalMass+=contained[l]->amt;
        }
        color.alpha=Color::colorBound(totalMass*.25);
        Draw::setColor(color);
        loc->fillRect(); 
    }
}
void Liquid::drawFlow()
{
//    if (saturatedMass>=getSaturation())
    {
        double magn=velocity->totalMovement();
        magn*=flowRate();
        magn/=10;
        Draw::setColor(Color::makeColor(magn,0,height()*25+20));
        loc->fillRect();
        if (Util::bad(magn))
        {
            Draw::setColor(Color(0,255,0));
            loc->fillRect();
        }
        else if (magn>0)
        {
            int midX=loc->px()+Square::halfSquareSize;
            int midY=loc->py()+Square::halfSquareSize;
            Dir* dir=Dir::North;
            for (int n=0;n<4;++n)
            {
                int current=velocity->get(dir);
                current*=flowRate();
                current/=4;
                Color::hue intensity=Color::colorBound(current);
                current*=1.6;
                int leng=Square::halfSquareSize * current/magn;
                Util::ensureBelow(leng,Square::halfSquareSize);

                if (Util::bad(velocity->get(dir)) || velocity->get(dir)<0)
                    Draw::setColor(Color::GREEN);
                else
                    Draw::setColor(Color(Color::WHITE,intensity));
                Draw::line(midX,midY,midX+dir->x()*leng,midY+dir->y()*leng);
                dir=dir->rotateClockwise();
            }
            Draw::setColor(Color(0,0,0));
            Draw::rect(midX-1,midY-1,2,2);
        }
    }
}
Color::hue Liquid::colorAlpha()const
{
    return Color::colorBound(height()*30);
}
void Liquid::changeMass(kilogram amt)
{
    mass+=amt;
    if (mass<0)
    {
        saturatedMass+=mass;
        mass=0;
        Util::ensurePositive(saturatedMass);
    }
}
void Liquid::giveLiquid(kilogram massAdd, LiquidType* type)
{
    if (type==getLiquidType())
        deltaMass+=massAdd;
    else
    {
        for (int l=0;l<contained.size();++l)
        {
            if (contained[l]->liquid==type) {
                contained[l]->deltaAmt+=massAdd;
                return;
            }
        }
        contained.push_back(new LiquidAmt(type,massAdd));
    }
}
kilogram Liquid::getTotalMass() const
{
    kilogram total=mass;
    for (int l=0;l<contained.size();++l)
    {
        total+=contained[l]->amt;
    }
    return total;
}
void Liquid::setAndSatMass(kilogram set)
{
    kilogram satur=getSaturation();
    if (set>satur)
    {
        set-=satur;
        saturatedMass=satur;
    }
    else {
        saturatedMass=set;
        return;
    }
    mass=set;
}
void Liquid::giveMass(kilogram amt)
{
    deltaMass+=amt;
}
void Liquid::addAndSatMass(kilogram amt)
{
    mass+=amt;
    kilogram satDiscrep=saturationDiscrepancy();
    if (satDiscrep>0)
    {
        mass-=satDiscrep;
        saturatedMass+=satDiscrep;
        if (mass<0)  {
            saturatedMass+=mass;
            mass=0;
        }
    }
}
void Liquid::zeroMass()
{
    mass=0;
    saturatedMass=0;
    deltaMass=0;
    for (int l=0;l<contained.size();++l) {
        delete contained[l];
    }
    contained.clear();
}
void Liquid::giveVelocity(Dir* dir, kilogram amt)
{
    deltaVel->unsafeChange(dir,amt);
}
kilogram Liquid::saturationDiscrepancy() const
{
    return getSaturation()-saturatedMass;
}
kilogram Liquid::getSaturation() const
{
    if (loc->getTerrain()==NULL)
    {
        cout<<"terrain is null\n";
        return 0;
    }
    return loc->getTerrain()->saturation();
}