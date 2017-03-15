/* 
 * File:   main.h
 * Author: Isaac
 *
 * Created on October 6, 2013, 6:32 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include "Ref/DisplayType.h"
#include "Gui/LoadingScreen.h"
#include "World/Game.h"

namespace Driver
{
    extern Game* game;
    
    extern bool ended;
    extern bool paused;
    extern int delay;
    extern long lastUpdate;
    extern LoadingScreen* loadingScreen;
    void setup();
    Game* loadGame();
    void run();
    void update();
    void draw();
    void end();
    void offloadGame();
    void close() ;
    
    void drawTimeBar();

}

#endif	/* MAIN_H */

