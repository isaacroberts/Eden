/* 
 * File:   Game.h
 * Author: Isaac
 *
 * Created on April 3, 2014, 12:44 AM
 */

#ifndef GAME_H
#define	GAME_H

#include "Grid.h"

class Game {
public:
    Game();
    virtual ~Game();
    
    inline Grid* getGrid() {
        return grid;
    }
    void update();
    void draw();
protected:
    Grid* grid;

    
    
};

#endif	/* GAME_H */

