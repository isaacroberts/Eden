/* 
 * File:   Gui.h
 * Author: Isaac
 *
 * Created on January 5, 2014, 9:02 PM
 */

#ifndef GUI_H
#define	GUI_H

#include <vector>
#include "Popup/_.h"
#include "Draw.h"
#include "../World/Square.h"

namespace Gui {
    void setup();
    void draw();
    
    //Map stuff
    extern int minPx,minPy,maxPx,maxPy;
    extern int permMinPx,permMinPy;
    void setGridScreenSize(int minX,int minY,int maxX,int maxY);
    
    extern byte globalRedraw;
    const int forceRedrawFreq=40;
    inline bool needsGlobalRedraw() {
        return globalRedraw;
    }
    inline void requireGlobalRedraw() {
        globalRedraw=2;
    }

    inline int xCenter(int offset) {
        return Draw::screenWidth/2 +offset;
    }
    inline int yCenter(int offset) {
        return Draw::screenHeight/2 + offset;
    }
    inline int yBelowScene(int offset) {
        return maxPy +offset;
    }
    inline int yFromBottom(int amtAbove) {
        return Draw::screenHeight-amtAbove;
    }
    inline int yBetweenSceneAndBottom(int offset) {
        return (maxPx+Draw::screenHeight)/2 +offset;
    }
    inline int xLeftScene(int distAway) {
        return minPx -distAway;
    }
    inline int xRightScene(int offset) {
        return maxPx+offset;
    }
    inline int xFromRight(int amtFromRight) {
        return Draw::screenWidth-amtFromRight;
    }
};

#endif	/* GUI_H */

