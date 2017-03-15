

#include <SDL/SDL_keycode.h>

#include "Event.h"

#include "../main.h"
#include "../World/Game.h"

#include "../World/Map.h"
#include "../Matter/Mobador.h"

#include "Gui.h"
#include "../Ref/Util.h"

namespace Event
{
    MapCommand::Type nextClick=MapCommand::None;
    Square* selected=NULL;
    Square* atCursor=NULL;
    byte shift=0;
    byte altPress=0;
    byte cmdPress=0;
    byte guiRedraw=2;
    list<TimeEvent*> pausedTimeEvents;
    PopupMenu* popup;
    void init()
    {
        popup=NULL;
        SDL_Event *event=new SDL_Event;
        while (SDL_PollEvent(event))
        {
            int pressDir=0;
            if (event->type==SDL_KEYDOWN)
                pressDir=1;
            else if (event->type==SDL_KEYUP)
                pressDir=-1;
            if (pressDir!=0)
            {
                SDL_Keycode keyCode=((SDL_KeyboardEvent*)event)->keysym.sym;
                if (keyCode==SDLK_LGUI || keyCode==SDLK_RGUI)
                    cmdPress+=pressDir;
                else if (keyCode==SDLK_LSHIFT || keyCode==SDLK_RSHIFT)
                    shift+=pressDir;
                else if (keyCode==SDLK_LALT || keyCode==SDLK_RALT)
                    altPress+=pressDir;
            }
        }
        delete event;
    }
    void draw()
    {
        if (atCursor!=NULL && selected!=NULL)
        {
            if (MapCommand::isDragged(nextClick))
            {
                if (selected->notError() && atCursor->notError())
                {
                    Gui::requireGlobalRedraw();
                    if (shift)
                    {
                        Draw::setColor(Color(30,30,30));
                        Draw::box(selected->px(),selected->py(),
                            atCursor->px(),atCursor->py(),
                            8,Square::squareSize,Square::squareSize);
                    }
                    else
                    {
                        Draw::setColor(Color(50,50,50,150));
                        Draw::translucentBox(selected->px(),selected->py(),
                            atCursor->px(),atCursor->py(), 
                            8,Square::squareSize,Square::squareSize);
                    
                    }
                }
            }
        }
    }
    //events handling
    bool checkEvents()
    {
        bool changesMade=false;
        SDL_Event *event=new SDL_Event;
        while (SDL_PollEvent(event))
        {
            if (handleEvent(event))
                changesMade=true;
        }
        delete event;
        return changesMade;
    }
    bool handleEvent(SDL_Event* event)
    {
        if (event->type==SDL_QUIT)
        {
            Driver::end();
            return true;
        }
        else if (event->type==SDL_KEYDOWN)
            return handleKeyPressedEvent((SDL_KeyboardEvent*)event);
        else if (event->type==SDL_KEYUP)
            return handleKeyReleasedEvent((SDL_KeyboardEvent*)event);
        else if (event->type==SDL_MOUSEBUTTONDOWN)
        {
            handleMousePressedEvent((SDL_MouseButtonEvent*)event);
            return true;
        }
        else if (event->type==SDL_MOUSEBUTTONUP)
        {
            handleMouseReleasedEvent((SDL_MouseButtonEvent*)event);
            return true;
        }
        else if (event->type==SDL_MOUSEMOTION)
            return handleMouseMotionEvent((SDL_MouseMotionEvent*)event);
        else if (event->type==SDL_WINDOWEVENT)
        {
            handleWindowEvent((SDL_WindowEvent*)event);
            return true;
        }
        return false;
    }//to handleevent
    bool handleKeyPressedEvent(SDL_KeyboardEvent* event)
    {
        SDL_Keycode keyCode=event->keysym.sym;
        if (keyCode==SDLK_ESCAPE)
        {
            cout<<"Exit by Escape key"<<endl;
            Driver::end();
        }
        else if (keyCode==SDLK_BACKSLASH) 
        {
            Gui::requireGlobalRedraw();
            Driver::paused=!Driver::paused;
        }
        else if (keyCode==SDLK_PERIOD)
        {
            changeDisplayType(DisplayType::Normal);
            Gui::requireGlobalRedraw();
            requireGuiRedraw();
        }
        else if (keyCode==SDLK_COMMA)
        {
            if (Driver::paused)
            {
                Driver::update();
                Driver::draw();
            }
            else
            {
                waitForKeyRelease(SDLK_COMMA);
            }
            Gui::requireGlobalRedraw();
        }
        else if (keyCode==SDLK_LSHIFT || keyCode==SDLK_RSHIFT)
            shift++;
        else if (keyCode==SDLK_LALT || keyCode==SDLK_RALT)
            altPress++;
        else if (keyCode==SDLK_LGUI || keyCode==SDLK_RGUI)
            cmdPress++;
        else if (keyCode==SDLK_LEFTBRACKET)
        {
            if (shift)
            {
                Driver::delay=0;
            }
            else
            {
                Driver::delay-=2;
                Util::ensurePositive(Driver::delay);
            }
        }
        else if (keyCode==SDLK_RIGHTBRACKET)
        {
            if (shift)
            {
                Driver::delay+=100;
                Util::ensureBelow(Driver::delay,400);
            }
            else
            {
                Driver::delay+=2;
                Util::ensureBelow(Driver::delay,400);
            }
        }
        //numbers
        else if (keyCode==SDLK_0)
            handleNumberPress(0);
        else if (keyCode==SDLK_1)
            handleNumberPress(1);
        else if (keyCode==SDLK_2)
            handleNumberPress(2);
        else if (keyCode==SDLK_3)
            handleNumberPress(3);
        else if (keyCode==SDLK_4)
            handleNumberPress(4);
        else if (keyCode==SDLK_5)
            handleNumberPress(5);
        else if (keyCode==SDLK_6)
            handleNumberPress(6);
        else if (keyCode==SDLK_7)
            handleNumberPress(7);
        else if (keyCode==SDLK_8)
            handleNumberPress(8);
        else if (keyCode==SDLK_9)
            handleNumberPress(9);
        else if (keyCode==SDLK_BACKQUOTE)
        {
            if (popup!=NULL)
            {
                //exit by one menu
                if (popup->backOut())
                    deletePopup();
            }
        }
        else if (keyCode==SDLK_p)
        {
            cout<<"Update "<<Util::frames<<endl;
            cout<<" Time = "<<Earth::timeOfDay<<" / "<<Earth::dayLength<<endl;
            if (atCursor!=NULL && atCursor->notError())
                atCursor->printInfo();
        }
        else if (keyCode==SDLK_RETURN)
            handleEnter();
        else if (keyCode==SDLK_LEFT)
        {
            handleArrowKey(Dir::West);
        }
        else if (keyCode==SDLK_RIGHT)
        {
            handleArrowKey(Dir::East);
        }
        else if (keyCode==SDLK_UP)
        {   
            handleArrowKey(Dir::North);
        }
        else if (keyCode==SDLK_DOWN)
        {
            handleArrowKey(Dir::South);
        }
        else if (keyCode==SDLK_MINUS)
        {
            GRID.changeSquareSize(shift?-10:-1);
        }
        else if (keyCode==SDLK_EQUALS)
        {
            GRID.changeSquareSize(shift?10:1);
        }
        else 
        {
            double moveSpeed=(shift?10:2);
            if (keyCode==SDLK_w)
            {
                if (cmdPress>0)
                {
                    cout<<"Exit by Cmd+W"<<endl;
                    Driver::end();
                }
                else
                {
                    Map::animal->accelerate(Dir::North,moveSpeed);
                }
            }
            else if (keyCode==SDLK_a)
            {
                Map::animal->accelerate(Dir::West,moveSpeed);
            }
            else if (keyCode==SDLK_s)
            {
                Map::animal->accelerate(Dir::South,moveSpeed);
            }
            else if (keyCode==SDLK_d)
            {
                Map::animal->accelerate(Dir::East,moveSpeed);
            }
            else return false;
        }
        return true;//returns true if the keypress was recognized
    }
    bool handleKeyReleasedEvent(SDL_KeyboardEvent* event)
    {
        SDL_Keycode keyCode=event->keysym.sym;
        if (keyCode==SDLK_LSHIFT || keyCode==SDLK_RSHIFT)
            shift--;
        else if (keyCode==SDLK_LALT || keyCode==SDLK_RALT)
            altPress--;
        else if (keyCode==SDLK_LGUI || keyCode==SDLK_RGUI)
            cmdPress--;
        else return false;
        return true;//returns true if the press was recognized
    }
    void handleMousePressedEvent(SDL_MouseButtonEvent* event)
    {
//        cout<<" Pressed Button = "<<(int)event->button<<endl;
        if (popup!=NULL)
        {
            popup->press();
            if (popup->onMouseMove(event->x,event->y))
            {
                removePopup(50);
            }
        }
        if (event->button==SDL_BUTTON_RIGHT)
        {//right click
            if (selected!=NULL && atCursor!=NULL && atCursor->notError())
                selected=NULL;
            else
                handleRightClick(event);
        }
        else if (event->button==SDL_BUTTON_LEFT)
        {//left click
            if (selected==NULL)
            {
                if (Util::onScene(event->x,event->y))
                    selected=atCursor;
                else
                {
                    
                }
            }
            else if (atCursor!=NULL && atCursor->notError())
                affectSelectedArea();
        }
    }
    void handleMouseReleasedEvent(SDL_MouseButtonEvent* event)
    {
//        cout<<" Released Button = "<<(int)event->button<<endl;
        if (popup!=NULL)
        {
            if (popup->onMouseClick(event->x,event->y))
            {//onMouseMove returns true if popup should be removed
                removePopup();
            }
        }
        if (event->button==SDL_BUTTON_LEFT)
        {
            if (selected!=NULL)
                affectSelectedArea();
        }
        else if (event->button==SDL_BUTTON_RIGHT)
        {
        }
    }//to handleMouseReleasedEvent
    bool handleMouseMotionEvent(SDL_MouseMotionEvent* event)
    {
        if (popup!=NULL)
        {
            if (popup->onMouseMove(event->x,event->y))
            {//onMouseMove returns true if popup should be removed
                removePopup();
            }
            return true;
        }
        else if (event->state & SDL_BUTTON_RMASK)
        {//right click & drag
        }
        else if (event->state & SDL_BUTTON_LMASK)
        {//left click & drag
            checkTimeBar(event->x,event->y);
            atCursor=GRID.getSquareByConformedPixel(event->x,event->y);
            if (atCursor->isError())//if click not on scene
            {
                atCursor=NULL;
            }
            if (selected!=NULL)
                return true;
        }
        else 
        {
            if (Util::onScene(event->x,event->y))
            {
                atCursor=GRID.getSquareByPixel(event->x,event->y);
                if (atCursor->isError())
                    atCursor=NULL;
            }
            else
            {
                atCursor=NULL;
                if (Util::roughlyInCircle(35,200,20,event->x,event->y))
                {//top popup menu circular button
                    Gui::requireGlobalRedraw();
//                            cout<<"clicked displaytype button\n";
                    addPopupMenu(new DisplayTypeMenu(20,185));
                    return true;
                }
                else if (Util::roughlyInCircle(35,270,20,event->x,event->y))
                {//bottom popup menu circular button
                    Gui::requireGlobalRedraw();
//                            cout<<"clicked mapcommand button\n";
                    addPopupMenu(new MapCommandMenu(20,255));
                    return true;
                }
            }
        }
        return false;
    }
    void handleRightClick(SDL_MouseButtonEvent* event)
    {
//        int x=event->x;
//        int y=event->y;
//        if (GRID.onScreen(x,y))
//            addPopupMenu(new DisplayTypeMenu(x,y));
    }
    void handleNumberPress(int num)
    {
        if (popup==NULL)
        {
            if (num==1)
            {
                addPopupMenu(new DisplayTypeMenu(20,185));
            }
            else if (num==2)
            {
                addPopupMenu(new MapCommandMenu(20,255));
            }
        }
        else
        {
            int option=num-1;
            if (num==0) option=9;
            if (popup->selectedOption(option))
                removePopup();
        }
        
    }
    void handleArrowKey(Dir* dir)
    {
        if (popup!=NULL)
        {
            if (dir->x()==0)
            {
                popup->shiftOption(dir->y()==-1);
            }
        }
        else
        {
            int amt=-Square::squareSize*(shift?5:1);
            moveScreen(dir->x()*amt,dir->y()*amt);
        }
    }
    void handleEnter()
    {
        if (popup!=NULL)
        {
            popup->selectCurrent();
            removePopup();
        }
    }
    void handleWindowEvent(SDL_WindowEvent* event)
    {
        int type=event->event;
        if (type==SDL_WINDOWEVENT_RESIZED)
        {
            Draw::resizeScreen(event->data1,event->data2);
        }
    }
    void moveScreen(int x, int y)
    {
        int cursorXPix;
        int cursorYPix;
        if (selected!=NULL && selected->notError())
        {
            cursorXPix=atCursor->px();
            cursorYPix=atCursor->py();
        }
        if (x!=0)
            GRID.changePixelXOffset(x);
        if (y!=0)
            GRID.changePixelYOffset(y);
        if (atCursor!=NULL && atCursor->notError())
            atCursor=GRID.getSquareByPixel(cursorXPix,cursorYPix);
    }
    void affectSelectedArea()
    {
        if (MapCommand::isDragged(nextClick))
        {
            if (selected!=NULL && selected->notError())
            {
                if (atCursor!=NULL && atCursor->notError())
                {
                    SDL_Rect affectedGridRect=Util::makeScreenRect(selected,atCursor);
                    //not used like actual SDL_Rect, just taking advantage
                        //of the fact thats its four ints

                    for (int y=affectedGridRect.y;y<=affectedGridRect.h;y++)
                    {
                        for (int x=affectedGridRect.x;x!=affectedGridRect.w;GRID.incX(x))
                        {
                            makeEffect(GRID.get(x,y));
                        }
                        makeEffect(GRID.get(affectedGridRect.w,y));
                    }
                }
            }
        }
        else
            makeEffect(atCursor);
        selected=NULL;
    }
    void makeEffect(Square* loc,MapCommand::Type type)
    {
        
        loc->requireRedraw();
        if (type==MapCommand::AddWater)
        {
            loc->getLiquid()->addAndSatMass((shift?150000:10000));
        }
        else if (type==MapCommand::Dry)
        {
            if (shift)
                loc->getLiquid()->zeroMass();
            else
                loc->getLiquid()->changeMass(-10000);
        }
        else if (type==MapCommand::Still)
        {
            loc->getSky()->getWind()->zero();
        }
        else if (type==MapCommand::Heat)
        {
            loc->getSky()->changeHeat(shift?600:50);
        }
        else if (type==MapCommand::Cool)
        {
            if (shift)
            {
                loc->getSky()->setHeat(1);
                loc->getTerrain()->setHeat(1);
                loc->getLiquid()->setHeat(1);
            }
            else
                loc->getSky()->changeHeat(-50);
        }
        else if (type==MapCommand::Dehumidify)
        {
            loc->getSky()->setHumidity(0);
        }
        else if (type==MapCommand::Mountain)
        {
            Gui::requireGlobalRedraw();
            if (shift)
                Map::makePeak(50,30,loc);
            else
                Map::makePeak(25,15,loc);
        }
        else if (type==MapCommand::Valley)
        {
            Gui::requireGlobalRedraw();
            if (shift)
                Map::makePeak(-50,30,loc);
            else
                Map::makePeak(-25,15,loc);
        }
        else if (type==MapCommand::Tree)
        {
            if (!loc->hasOccOfType(ThingType::Tree_T))
            {
                if (shift) {
                    Tree* tree=Map::makeTree(loc,FruitType::Apple,10000);
                    if (tree!=NULL)
                        tree->setFruitAmt(5);
                }
                else
                    Map::makeTree(loc,FruitType::Apple,3000);
            }
        }
        else if (type==MapCommand::Till)
        {
            loc->clearTerrain();
            if (shift)
                loc->clearAllOccupants();
        }
    }
    void makeGlobalEffect(MapCommand::Type type)
    {
        for (int x=0;x<GRID.xAmt;x++)
        {
            for (int y=0;y<GRID.yAmt;y++)
            {
                makeEffect(GRID.get(x,y),type);
            }
        }
    }
    void changeDisplayType(DisplayType::Type changeTo)
    {
        if (changeTo==DisplayType::Normal
                && displayType!=DisplayType::Normal)
            Gui::requireGlobalRedraw();
        displayType=changeTo;
    }
    void popupMapCommandSelect(MapCommand::Type type, int x, int y)
    {
        if (MapCommand::isDragged(type))
        {
            if (MapCommand::canBeGlobal(type) && altPress)
            {
                    makeGlobalEffect(type);
            }
            else
                nextClick=type;
        }
        else
        {
            nextClick=type;
        }
    }
    void onClickTypePress(MapCommand::Type type)
    {
        if (altPress>0 && MapCommand::canBeGlobal(type))
            makeGlobalEffect(type);
        else
            nextClick=type;
            
    }
    void checkTimeBar(int x,int y)
    {
//        if (selected!=NULL || selected->notError()) 
//        {
//            return;
//        }
        SDL_Rect rect=(SDL_Rect){600,920,200,30};
        if (Util::contains(&rect,x,y))
        {
            guiRedraw=true;
            Driver::delay=(x-600)/2;
        }
    }
/*-----Time Event Stuff--------------*/
    void queuePausedEvent(long delay,void (*event)())
    {
        TimeEvent* insert=new TimeEvent(SDL_GetTicks()+delay,event);
        bool inserted=false;
        for (list<TimeEvent*>::iterator iter=pausedTimeEvents.begin();
                iter!=pausedTimeEvents.end();iter++)
        {
            if ((*iter)->time>insert->time)
            {
                pausedTimeEvents.insert(iter,insert);
                inserted=true;
            }
        }
        if (!inserted)
            pausedTimeEvents.push_back(insert);
    }
    void checkTimeEvents()
    {
        if (!pausedTimeEvents.empty())
        {
            long curTime=SDL_GetTicks();
            list<TimeEvent*>::iterator iter=pausedTimeEvents.begin();
            while (iter!=pausedTimeEvents.end() &&
                     curTime >= (*iter)->time )
            {
                (*iter)->event();
                iter++;
            }
            if (iter!=pausedTimeEvents.begin())
            {
                while (iter!=pausedTimeEvents.begin())
                    pausedTimeEvents.pop_front();
                Event::requireGuiRedraw();
                Gui::requireGlobalRedraw();
            }
        }
    }
    
/*-----Popup Menu Stuff--------------*/
    void addPopupMenu(PopupMenu* pop)
    {
        if (popup!=NULL)
        {
            deletePopup();
        }
        popup=pop;
    }
    void removePopup(long delay)
    {
        queuePausedEvent(delay,deletePopup);
    }
    void deletePopup()
    {   
        if (popup==NULL)
            return;
        delete popup;
        popup=NULL;
        Gui::requireGlobalRedraw();
        requireGuiRedraw();
    }
/*-----GUI type stuff---------------*/
    void waitForKeyRelease(SDL_Keycode key)
    {
        SDL_Event *event=new SDL_Event;
        while (true)
        {
            SDL_Delay(20);
            while (SDL_PollEvent(event))
            {
                if (event->type==SDL_KEYUP)
                {
                    if (event->key.keysym.sym==key)
                    {
                        delete event;
                        return;
                    }
                }
            }
        }
    }
    
    void checkForExit()
    {
        SDL_Event* event=new SDL_Event;
        while (SDL_PollEvent(event))
        {
            if (event->type==SDL_KEYDOWN)
            {
                SDL_Keycode keyCode=((SDL_KeyboardEvent*)event)->keysym.sym;
                if (keyCode==SDLK_ESCAPE)
                {
                    Driver::ended=true;
                    Driver::close();
                    cout<<"Exit during initialization on command of  user"<<endl;
                    cout<<"during  \""<<Driver::loadingScreen->getCurMessage()<<"\" phase"<<endl;
                    exit(0);
                }
                else if (keyCode==SDLK_LGUI || keyCode==SDLK_RGUI)
                    cmdPress++;
                else if (keyCode==SDLK_w)
                {
                    if (cmdPress>0)
                    {
                        Driver::ended=true;
                        Driver::close();
                        cout<<"Exit during initialization on command of  user"<<endl;
                        cout<<"during  \""<<Driver::loadingScreen->getCurMessage()<<"\" phase"<<endl;
                        exit(0);
                    }
                }
            }
            else if (event->type==SDL_KEYUP)
            {
                SDL_Keycode keyCode=((SDL_KeyboardEvent*)event)->keysym.sym;
                if (keyCode==SDLK_LGUI || keyCode==SDLK_RGUI)
                    cmdPress--;
            }
        }
        delete event;
    }
    void requireGuiRedraw()
    {
        guiRedraw=2;
    }
}