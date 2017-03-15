/* 
 * File:   PopupMenu.h
 * Author: Isaac
 *
 * Created on January 5, 2014, 12:17 AM
 */

#ifndef POPUPMENU_H
#define	POPUPMENU_H

#include <string>

using namespace std;

class PopupMenu 
{
public:
    static const int optionHeight;
    PopupMenu(int x,int y);
    void construct();
//    PopupMenu(const PopupMenu& orig);
    virtual void draw();
    virtual void shiftOption(bool up);
    virtual bool onMouseMove(int x,int y);//returns true if should be removed
    virtual bool onMouseClick(int x,int y);//should return true if menu should be removed
    virtual bool backOut(){//returns true if should exit
        return true; }
    virtual void selectCurrent() {
        pressed=true;
        handleOptionClick(optionSelected);
    }
    virtual void highlightOption(int num) {
        if (num>0 && num<optionAmt())
            optionSelected=num;
    }
    virtual bool selectedOption(int num) {
        pressed=true;
        return handleOptionClick(num);
    }
    inline void press() {
        pressed=true;
    }
    virtual int getOptionAt(int x,int y);//returns -1 on OOB,-2 on none found
    virtual string getOption(int optionNumber)=0;
    virtual int optionAmt()=0;
    virtual ~PopupMenu();
    enum PopupType {
        MapCommand,DisplayType,None
    };
    virtual PopupType getType()=0;
protected:
    int x,y;
    int height,width;
    int optionSelected;
    bool pressed;
    
    virtual bool handleOptionClick(int optionClicked)=0;
    bool withinBox(int x,int y,int tolerance);
    void repositionIfOOB();
};

#endif	/* POPUPMENU_H */

