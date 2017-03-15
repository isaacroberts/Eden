/* 
 * File:   PopupMenu.cpp
 * Author: Isaac
 * 
 * Created on January 5, 2014, 12:17 AM
 */

#include "PopupMenu.h"
#include "../Draw.h"
#include "../../World/Square.h"
#include "../Gui.h"
const int PopupMenu::optionHeight=17;

PopupMenu::PopupMenu(int setX,int setY) 
{
    x=setX;
    y=setY;
    width=30;
    height=optionHeight;
    optionSelected=0;
}
void PopupMenu::construct()
{
    int amt=optionAmt();
    width=1;
    for (int n=0;n<amt;n++)
    {
        int curWid=getOption(n).size();
        Util::ensureAbove(width,curWid);
    }
    width*=optionHeight;
    width*=.6;
    width+=5;
    height=amt*optionHeight;
    repositionIfOOB();
    pressed=false;
}
PopupMenu::~PopupMenu() {
}
void PopupMenu::draw()
{
    int amt=optionAmt();
    int curY=y;
    Draw::setFont(false,optionHeight-2);
    for (int o=0;o<amt;o++)
    {
        if (o==optionSelected)
        {
            if (pressed)
                Draw::setColor(227,119,52);
            else
                Draw::setColor(130-o*5,130-o*5,180-o*5);
        }
        else
            Draw::setColor(100-o*5,130-o*5,130-o*5);
        Draw::rect(x,curY,width,optionHeight);
        Draw::setColor(Color::WHITE);
        if (o<=9)
        {
            char num[]={o+49,'\0'};
            if (o==9)
                num[0]='0';
            Draw::text(num,x+3,curY+1);
        }
        Draw::text(getOption(o).c_str(),x+11,curY+1);
        curY+=optionHeight;
    }
}
void PopupMenu::shiftOption(bool up)
{
    if (pressed) return;
    if (up)
    {
        optionSelected--;
        if (optionSelected<0)
            optionSelected=optionAmt()-1;
        
    }
    else
    {
        optionSelected++;
        if (optionSelected>=optionAmt())
            optionSelected=0;
    }
}
bool PopupMenu::onMouseMove(int mx, int my)
{
    int option=getOptionAt(mx,my);
    if (option==-1)//if mouse OOB
        return true;//remove self
    else if (option==-2)//if mouse not over option
        return false;//dont remove self
    else {//else if mouse over option
        optionSelected=option;//highlight option
        return false;//and dont remove self
    }
}
bool PopupMenu::onMouseClick(int mx, int my)
{
    int option=getOptionAt(mx,my);
    if (option== -1)//if mouse OOB
        return true;//remove self
    else if (option== -2)//if mouse not over option
        return false;//dont remove self
    else {//else if mouse over option
        pressed=true;
        handleOptionClick(option);
        return true;
    }
}
int PopupMenu::getOptionAt(int mx, int my)
{
    if (!withinBox(mx,my,2))
        return -1;//returns -1 on OOB
    int amt=optionAmt();
    int curY=y;
    for (int o=0;o<amt;o++)
    {
        curY+=optionHeight;
//        cout<<"checking "<<o<<endl;
        if (my<curY)
        {
            return o;
        }
    }
    return -2;//returns -2 on none found
}
bool PopupMenu::withinBox(int mx, int my,int tolerance)
{
    if (mx<x-tolerance)//if mouse left of box
        return false;
    if (mx>x+width+tolerance)//if mouse right of box
        return false;
    if (my<y-tolerance)//if mouse above box
        return false;
    if (my>y+height+tolerance)//if mouse below box
        return false;
    return true;
}
void PopupMenu::repositionIfOOB()
{
    if (y+height>Gui::maxPy)
    {
        y-=height;
    }
}