/* 
 * File:   DisplayTypeMenu.h
 * Author: Isaac
 *
 * Created on January 18, 2014, 1:34 PM
 */

#ifndef DISPLAYTYPEMENU_H
#define	DISPLAYTYPEMENU_H

#include "PopupMenu.h"
#include "../../Ref/DisplayType.h"

using namespace std;

class DisplayTypeMenu : public PopupMenu
{
public:
    DisplayTypeMenu(int x,int y);
    virtual ~DisplayTypeMenu();
    bool handleOptionClick(int optionClicked);
    virtual string getOption(int optionNumber);
    inline int optionAmt() {
        return DisplayType::selectableAmt;
    }

    inline PopupMenu::PopupType getType()
        {return PopupMenu::DisplayType;}
private:

};

#endif	/* DISPLAYTYPEMENU_H */

