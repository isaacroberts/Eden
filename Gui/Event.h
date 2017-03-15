/* 
 * File:   Events.h
 * Author: Isaac
 *
 * Created on October 6, 2013, 6:51 PM
 */

#ifndef EVENTS_H
#define	EVENTS_H

#include <SDL.h>
#include "../World/Square.h"

#include "../Ref/MapCommand.h"
#include "Popup/MapCommandMenu.h"
#include "../Gui/Popup/_.h"

namespace Event
{
    extern MapCommand::Type nextClick;
    extern Square* selected;
    extern Square* atCursor;
    extern byte shift;
    extern byte altPress;
    extern byte cmdPress;
    extern byte guiRedraw;
    void init();
    
    void draw();
    
    bool checkEvents();//returns true if there were any events
/*----Event if-ladders---------*/
    //bool-return events return true if anything is changed
    bool handleEvent(SDL_Event*);
    bool handleKeyPressedEvent(SDL_KeyboardEvent*);
    bool handleKeyReleasedEvent(SDL_KeyboardEvent*);
    void handleMousePressedEvent(SDL_MouseButtonEvent*);
    void handleMouseReleasedEvent(SDL_MouseButtonEvent*);
    bool handleMouseMotionEvent(SDL_MouseMotionEvent*);
    void handleRightClick(SDL_MouseButtonEvent*);
    void handleWindowEvent(SDL_WindowEvent*);
    void handleArrowKey(Dir* dir);
    void handleNumberPress(int num);
    void handleEnter();
    
/*------Time Event stuff----------------*/
    struct TimeEvent {
        long time;
        void (*event)();
        TimeEvent(long setTime,void (*setEvent)())
                : time(setTime),event(setEvent) {}
    };
    extern list<TimeEvent*> pausedTimeEvents;//checked while paused or running
//    vector<TimeEvent> runningTimeEvents;//based on gametime updates
    void queuePausedEvent(long delay,void* (*event)());
//    void queueRunningEvent(long delay,void* (*event));
//    void queueEvent(long delay,void* (*event),bool paused);
    
    void checkTimeEvents();
    
/*-----Popup Menu Stuff---------*/
    extern PopupMenu* popup;
    void addPopupMenu(PopupMenu*);
    void removePopup(long delay);
    inline void removePopup() {
        removePopup(100);     }
    void deletePopup();
/*-----Square Screen----------*/
    void moveScreen(int x,int y);
/*------Checks before effects are applied--------*/
    void changeDisplayType(DisplayType::Type changeTo);
    void popupMapCommandSelect(MapCommand::Type,int x,int y);//x,y is location of PopupMenu's original leftclick
    void onClickTypePress(MapCommand::Type);
    void affectSelectedArea();
/*-----Functions that actually do stuff---------*/
    void makeGlobalEffect(MapCommand::Type type);
    void makeEffect(Square* loc,MapCommand::Type type);
    inline void makeEffect(Square* loc){makeEffect(loc,nextClick);}
    void checkTimeBar(int x,int y);
/*------Functions that change Gui*/
    void waitForKeyRelease(SDL_Keycode key);
    void checkForExit();
    void requireGuiRedraw();
}




#endif	/* EVENTS_H */

