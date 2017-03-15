/* 
 * File:   MapCommandMenu.h
 * Author: Isaac
 *
 * Created on January 5, 2014, 8:44 PM
 */

#ifndef MAPCOMMANDMENU_H
#define	MAPCOMMANDMENU_H

#include "PopupMenu.h"

class MapCommandMenu : public PopupMenu
{
public:
    MapCommandMenu(int x,int y);
//    MapCommandMenu(const MapCommandMenu& orig);
    virtual ~MapCommandMenu();
    bool handleOptionClick(int optionClicked);
//    virtual void draw();
    virtual string getOption(int optionNumber);
    virtual int optionAmt();
    
    inline PopupMenu::PopupType getType()
        {return PopupMenu::MapCommand;}
};

#endif	/* MAPCOMMANDMENU_H */

