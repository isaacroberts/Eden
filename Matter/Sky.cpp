/* 
 * File:   Sky.cpp
 * Author: Isaac
 * 
 * Created on October 18, 2013, 4:33 PM
 */

#include "Sky.h"
#include "../World/Game.h"
#include "../World/Map.h"

Sky::Sky() : Fluid()
{
    loc=Grid::squerror;
    heat=Map::getDefaultHeat();
    humidity=Map::getDefaultHumidity();
    mass=1.225*getVolume();
    deltaHeat=0;
    deltaMass=0;
}
Sky::~Sky() 
{
}
//vishnu functions
void Sky::preStep()
{
//    velocity->zero();
    velocity->multiply(.3);
}
void Sky::update()
{
    diffuse(loc->transform(Dir::West)->getSky());
    diffuse(loc->transform(Dir::North)->getSky());
    Dir* dir=Dir::East;
    for (int n=0;n<4;++n) 
    {
        Square* blowTo=loc->transform(dir);
        calcWind(blowTo,dir);
        double blow=velocity->get(dir);
        sendWind(blowTo->getSky(),dir,blow);
        dir=dir->rotateClockwise();
    }
}
void Sky::calcWind(Square* blowTo,Dir* dir)
{
    if (blowTo->isError()) 
    {
        velocity->set(dir,0);
        return;
    }
    if (dir==NULL) dir=loc->getDir(blowTo);
    Sky* with=blowTo->getSky();
    float blow=pressure()-with->pressure();
    blow/=Earth::airSpecificGasConstant;
    blow*=Earth::TIME_STEP;
    blow*=4;
    if (blow>=0)
    {
        blow/=heat*getVolume();
        velocity->change(dir,blow);
    }
    else
    {
        blow/=with->getHeat()*with->getVolume();
        blow=-blow;
        //take away wind from 
        if (velocity->get(dir)<blow)
        {
            blow-=velocity->get(dir);
            velocity->set(dir,0);
            with->getWind()->change(dir->opposite(),blow);
        }
        else 
        {
            velocity->change(dir,-blow);
        }
    }
}
void Sky::sendWind(Sky* other,Dir* dir,double blow)
{
    if (other==NULL) return;
    if (dir==NULL) dir=loc->getDir(other->getLoc());
    Util::ensureBelow(blow,mass*.95);
    
    float avgHeat=heat*blow+other->getHeat()*other->getMass();
    avgHeat/=blow+other->getMass();
    avgHeat-=other->getHeat();
    other->giveHeat(avgHeat);
    
    float humidityCarried=humidity/mass * blow;
    humidity-=humidityCarried;
    other->changeHumidity(humidityCarried);
    
    float windSend=velocity->get(dir)*blow;
    windSend/=(blow+other->getMass());
    other->getWind()->change(dir,windSend);
    
    giveMass(-blow);
    other->giveMass(blow);
    
}
void Sky::diffuse(Sky* with)
{
    if (with==NULL) return;
    if (getMass()<=.001) return;
    if (with->getMass()<=.001) return;
    float heatTransfer=heat - with->getHeat();
    heatTransfer/=4;
    //assume specific heat are the same for both Skys
    giveHeat(-heatTransfer/mass);
    with->giveHeat(heatTransfer/with->getMass());
    
    float deltaHumid=humidity*.7 - with->getHumidity()*.7;
    giveHumidity(-deltaHumid);
    with->giveHumidity(deltaHumid);
    Square* onePast=with->getLoc()->transform(loc->getDir(with->getLoc()));
    deltaHumid=humidity*.3 - onePast->getSky()->getHumidity()*.3;
    giveHumidity(-deltaHumid);
    onePast->getSky()->giveHumidity(deltaHumid);
}
void Sky::exchange(Square* with)
{
    if (with->getTerrain()->underwater())
    {
        exchangeHeat(with->getLiquid(),100,1);
    }
    else
    {
        exchangeHeat(with->getTerrain(),100,with->getTerrain()->surfaceArea());
    }
}
void Sky::endStep()
{
    changeHeat(deltaHeat);
    changeMass(deltaMass);
    deltaHeat=0;
    deltaMass=0;
    exchange(loc);
}
bool Sky::takeMoisture(float amt)
{
    if (humidity>=amt)
    {
        humidity-=amt;
        return true;
    }
    else
    {
        //TODO: decide if humidity should be set to zero here
        return false;
    }
}
//graphics
void Sky::paint()
{
    if (displayType==DisplayType::Humidity)
        drawHumidity();
    else if (displayType==DisplayType::Heat)
        drawHeat();
    else if (displayType==DisplayType::Wind)
        drawWind();
    else if (displayType==DisplayType::AirMass)
        drawMass();
}
void Sky::drawHumidity()
{
    if (Util::bad(humidity))
        Draw::setColor(Color::GREEN);
    else
    {
        Color::hue blu=Color::colorBound(humidity*100);
        Draw::setColor(Color(0,0,blu));
    }
    loc->fillRect();
}
void Sky::drawHeat()
{
    if (Util::bad(heat))
    {
        Draw::setColor(Color::GREEN);
    }
    else
    {
        int drawHeat=heat-Map::getDefaultHeat();
//        drawHeat*=2;
        drawHeat+=125;
        Color::hue r=Color::colorBound(drawHeat);
        Draw::setColor(Color::makeColor(r,0,255-r));
    }
    loc->fillRect();
}
void Sky::drawWind()
{
    float magn=velocity->totalMovement();
    if (Util::bad(magn) || magn<0)
    {
        Draw::setColor(Color::GREEN);
        loc->fillRect();
        return;
    }
    int midX=loc->px()+Square::halfSquareSize,midY=loc->py()+Square::halfSquareSize;
    if (magn>0)
    {
        magn*=1E+6;
        Draw::setColor(Color::makeColor(magn,0,255-magn));
        loc->fillRect();
        Dir* dir=Dir::North;
        for (int n=0;n<4;++n)
        {
            float vel=velocity->get(dir);
            if (vel>4E-7)
            {
                int windPower=vel*2.5E+6;
                Color::hue intensity=Color::colorBound(windPower*10);
                int leng=Square::halfSquareSize * windPower/magn;
                Util::ensureBelow(leng,Square::halfSquareSize);
                if (leng>0)
                {
                    Draw::setColor(Color(Color::WHITE,intensity));
                    Draw::line(midX,midY,midX+dir->x()*leng,midY+dir->y()*leng);
                }
            }
            else if (Util::bad(vel) || vel<0)
                Draw::setColor(Color::GREEN);
            dir=dir->rotateClockwise();
        }
    }
    else
    {
        Draw::setColor(Color::BLUE);
        loc->fillRect();
    }
    Draw::setColor(Color::BLACK);
    Draw::rect(midX-1,midY-1,1,1);
}
void Sky::drawMass()
{
    Color::hue turq=Color::colorBound(mass*100);
    Draw::setColor(Color(0,turq,turq));
    loc->fillRect();
}
void Sky::printInfo() const
{
    cout<<"  Air:"<<endl;
    Fluid::printInfo();
    cout<<"    Humidity="<<humidity<<endl;
    
//    cout<<"    Volume="<<getVolume<<endl;
    
}
//info getters
//mutators
void Sky::giveMass(float amt)
{
    deltaMass+=amt;
}
void Sky::giveHeat(float amt)
{
    deltaHeat+=amt;
}
void Sky::giveWind(const Vector add)
{
    velocity->add(&add);
}
void Sky::giveHumidity(float amt)
{
    humidity+=amt;
}