/* 
 * File:   DisplayTypeMenu.cpp
 * Author: Isaac
 * 
 * Created on January 18, 2014, 1:34 PM
 */

#include "DisplayTypeMenu.h"

DisplayTypeMenu::DisplayTypeMenu(int x,int y) : PopupMenu(x,y)
{
    construct();
}

DisplayTypeMenu::~DisplayTypeMenu() 
{
}

bool DisplayTypeMenu::handleOptionClick(int option)
{
    if (option<DisplayType::selectableAmt)
    {
        optionSelected=option;
        displayType=DisplayType::selectable[option];
    }
    else
    {
        optionSelected=0;
        displayType=DisplayType::Normal;
    }
    return true;
}
string DisplayTypeMenu::getOption(int optionNumber)
{
    return DisplayType::getName(DisplayType::selectable[optionNumber]);
}