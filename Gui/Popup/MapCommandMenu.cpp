/* 
 * File:   MapCommandMenu.cpp
 * Author: Isaac
 * 
 * Created on January 5, 2014, 8:44 PM
 */

#include "MapCommandMenu.h"
#include "../../Ref/MapCommand.h"
#include "../../Ref/Util.h"
#include "../Event.h"

MapCommandMenu::MapCommandMenu(int setX,int setY) : PopupMenu(setX,setY)
{
    construct();
}
MapCommandMenu::~MapCommandMenu() {
}
bool MapCommandMenu::handleOptionClick(int option)
{
    if (option>=int(MapCommand::None))//if cancel was clicked
    {
        //do nothing
        optionSelected=(int)MapCommand::None;
        return true;
    }
    else { 
        optionSelected=option;
        //hand off command to Event
        Event::popupMapCommandSelect(MapCommand::Type(option),x,y);
        return true;
    }
}
string MapCommandMenu::getOption(int optionNumber)
{
    return MapCommand::getName(MapCommand::Type(optionNumber));
}
int MapCommandMenu::optionAmt()
{
    return MapCommand::None+1;//none is last element and should be displayed
}