#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <limits>
#include <list>
//#include <google/profiler.h>

#include "main.h"

#include "_.h"

using namespace std;

bool Driver::ended=false;
bool Driver::paused=true;
int Driver::delay=10;
long Driver::lastUpdate=0;
LoadingScreen* Driver::loadingScreen;
DisplayType::Type displayType=DisplayType::Normal;
Game* Driver::game;

int main( int argc, char** argv )
{
    cout<<"Setting up\n";
    
    Driver::setup();
    Driver::run();
    Driver::close();
    return 0;
}

namespace Driver
{
    void setup() 
    {
        srand(time(NULL));
        Draw::init();
        Color::init();
        loadingScreen=new LoadingScreen();
        loadingScreen->display();
        //enum initialization
        Dir::initialize();
        //game initialization
        Event::init();
        Event::nextClick=MapCommand::None;
        displayType=DisplayType::Normal;
        lastUpdate=SDL_GetTicks();
        Draw::clrScrn();
        SDL_Event *event=new SDL_Event;
        while (SDL_PollEvent(event)){}
        delete event;
        Event::guiRedraw=true;
        
        loadGame();
        
        draw();
//        Draw::clrScrn();
    }
    Game* loadGame()
    {
        LiquidType::initialize();
        ThingType::initialize();
        FruitType::initialize();
        
        int minX=70,minY=40,   maxX=1460,maxY=900;
        Gui::setGridScreenSize(minX,minY,maxX,maxY);
        
        game=new Game();
        
        Animalia::originOfSpecies();
        Map::makeWorld();
        
        return game;
    }
    void run()
    {
        cout<<"Running"<<endl;
        const bool displayUpdateTime=false;
        while(!ended)
        {
            long startTime;
            if (displayUpdateTime)
                startTime=SDL_GetTicks();
            if (!paused)
            {
                update();
                if (displayUpdateTime)
                    printf("update time = %4ld",(SDL_GetTicks()-startTime));
                if (displayUpdateTime)
                    startTime=SDL_GetTicks();
                draw();
                if (displayUpdateTime)
                    cout<<"      draw time = "<<(SDL_GetTicks()-startTime)<<endl;
            }
            int waitFor=lastUpdate+delay;
            lastUpdate=SDL_GetTicks();
            waitFor-=lastUpdate;
            if (waitFor>0)
                SDL_Delay(waitFor);
            Event::checkTimeEvents();
            bool shitChanged= Event::checkEvents();
            if (paused && shitChanged)
            {
                if (displayUpdateTime)
                    startTime=SDL_GetTicks();
                draw();
                if (displayUpdateTime)
                    cout<<"Pause draw time = "<<(SDL_GetTicks()-startTime)<<endl;
            }
        }
    }
    void end() {
        ended=true;
    }
    void offloadGame()
    {
        delete game;
    }
    void close() {
        offloadGame();
        ThingType::end();
        Draw::end();
    }

    void update()
    {
        Util::frames++;
        Earth::update();
        game->update();
    }
    void draw() {
        Draw::preDraw();
        game->draw();
        Event::draw();
        Map::draw();
        Gui::draw();
        if (paused)
        {
            Draw::setFont(true,200);
            Draw::text("Paused",Gui::xCenter(-300),Gui::yCenter(-100),Color(250,250,250));
        }
        drawTimeBar();
        Draw::postDraw();
    }
    void drawTimeBar()
    {
        if (Event::guiRedraw)
        {
            SDL_Rect line={600,930,200,5};
            Draw::setColor(Color(80,80,80));
            Draw::rect(&line);
            SDL_Rect dial={600+delay/2,925,15,15};
            Draw::setColor(Color(150,0,150));
            Draw::rect(&dial);
        }
    }
}