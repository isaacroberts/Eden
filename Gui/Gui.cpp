/* 
 * File:   Gui.cpp
 * Author: Isaac
 * 
 * Created on January 5, 2014, 9:02 PM
 */

#include "Gui.h"

#include "Event.h"

namespace Gui
{
    int minPx,minPy,maxPx,maxPy;
    int permMinPx,permMinPy;
    byte globalRedraw;
    void setup()
    {
        
    }
    void setGridScreenSize(int minX, int minY, int maxX, int maxY)
    {
        permMinPx=minX;
        permMinPy=minY;
        Gui::minPx=minX;
        Gui::minPy=minY;
        Gui::maxPx=maxX;
        Gui::maxPy=maxY;
    }

    void draw()
    {
        //popup menu buttons
        Draw::setColor(20,50,50);
        Draw::circle(35,200,20);
        Draw::circle(35,270,20);
        Draw::setColor(255,255,255,5);
        for (int n=0;n<20;n++)
        {
            Draw::circle(35,200,n);
            Draw::circle(35,270,n);
        }
        //Little time of day square
        int yel=255*Earth::timeOfDaySunFactor;
        int blu=255*(cos(6.28*abs(float(Earth::timeOfDay)/Earth::dayLength)));
        Util::ensurePositive(blu);
        Draw::setColor(yel,yel*.9,blu);
        Draw::rect(Gui::xLeftScene(0),Gui::yBelowScene(20),20,20);
        
        //popup menus
        if (Event::popup!=NULL)
            Event::popup->draw();
    }
}