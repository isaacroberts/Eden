/* 
 * File:   LoadingScreen.cpp
 * Author: Isaac
 * 
 * Created on October 10, 2013, 5:53 PM
 */

#include "LoadingScreen.h"

#include "Draw.h"

LoadingScreen::LoadingScreen() 
{
    percentage=0;
    task=Setup;
    taskChanged=2;
}
void LoadingScreen::display()
{
    Draw::setColor(Color(0,60,0));
//    Draw::fillScreen();
    SDL_Rect outline=(SDL_Rect){400,450,600,100};
    if (taskChanged)
    {
        SDL_Rect rect=(SDL_Rect){0,0,Draw::screenWidth,Draw::screenHeight};
        SDL_FillRect(Draw::textScreen,&rect,0);    
        Draw::fillScreen();
    }
    else
    {
        Draw::rect(&outline);
    }
    SDL_Rect loadBar=(SDL_Rect){400,450,percentage*600,100};
    Draw::setColor(Color(0,0,200));
    Draw::rect(&loadBar);
    Draw::traceRect(&outline);
    if (taskChanged)
    {
        Draw::setFontSize(40);
        Draw::text(getMessage(task).c_str(),410,405,Color(250,250,250));
        taskChanged--;
    }
    else
        Draw::drewText=false;
    
    Draw::postDraw();
}
void LoadingScreen::setTask(Task set)
{
    task=set;
    percentage=0;
    taskChanged=2;
    display();
}
void LoadingScreen::setCurrent(float setPercent, Task setTask)
{
    if (task!=setTask)
    {
        taskChanged=2;
        task=setTask;
    }
    percentage=setPercent;
    display();
}
string LoadingScreen::getMessage(Task task)
{
    switch (task)
    {
        case Setup:
            return "Initializing Light";
        case Square:
            return "Allocating the heavens";
        case Mountains:
            return "Establishing a Firmament";
        case Spring:
            return "Defining the oceans";
        case Occupants:
            return "Filling the Earth with life";
        case Forest:
            return "Loading the Plants and the Trees";
        default:
            cout<<"No message for task "<<task<<endl;
            exit(1);
    }
}