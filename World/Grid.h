/* 
 * File:   Grid.h
 * Author: Isaac
 *
 * Created on April 3, 2014, 12:51 AM
 */

#ifndef GRID_H
#define	GRID_H

#include <vector>
#include "Square.h"

#include "../Gui/Gui.h"

class Grid {
public:
    
    Grid(int x,int y);
    virtual ~Grid();
    
public:
    //members
    static Square* squerror;

    int xAmt,yAmt;
    
    
    //doing functions
    void drawAll();
    void updateAll();
    void removeFromQus();
public:
    //square-getting functions
    Square* get(int x,int y);
    inline Square* getSquare(int x,int y) {return get(x,y);}
    Square* getRandSquare();
    Square* getNrstValidSquare(int px,int py);
    //list-of-square getting functions
    vector<Square*>* getSquaresInRadius(Square* center,int radius);
    vector<Square*>* getSquareOfSquares(Square* center,int radius);
    float getChunkElevation(int xFrom,int yFrom,int xTo,int yTo);
    void changeChunkElevation(int xFrom,int yFrom,int xTo,int yTo,float amt);
    
    void queueThingMovement(Thing*,Square* moveTo);
    
    inline bool xInBounds(int x){
        return x>=0 && x<xAmt;
    }
    inline bool yInBounds(int y) {
        return y>=0 && y<yAmt;
    }
    inline bool inBounds(int x,int y) {
        return xInBounds(x) && yInBounds(y);
    }
    inline void addToVector(vector<Square*>* vec,int gx,int gy) {
        if (yInBounds(gy)) {
            gx=wrapX(gx);
            vec->push_back(grid[gx][gy]);
        }
    }
    inline int amt() {  return xAmt*yAmt; }
    inline void safeIncX(int& x) {x++; while (x>=xAmt) x-=xAmt;}
    inline void incX(int& x) {x++; if (x==xAmt)(x)=0;}
    //screen
    
    int totalXPixels();
    int totalYPixels();
    int validizeY(int y);
    int validizeX(int x);
    int screenConformY(int py);
    int screenConformX(int px);
    int wrapX(int x);
    int screenWrapX(int px);
    int getGridXByPixel(int px);
    int getGridYByPixel(int py);
    bool onScreen(int px,int py);
    Square* getSquareByPixel(int px,int py);
    Square* getSquareByConformedPixel(int px,int py);
    inline int getPixelXOffset(){return xPixelOffset+Gui::minPx;}
    inline int getPixelYOffset(){return yPixelOffset+Gui::minPy;}
    
    inline int pixHeight() {return Gui::maxPy-Gui::minPy;}
    inline int pixWidth(){return Gui::maxPx-Gui::minPx;}
    //scroll functions
    void changePixelXOffset(int amt);
    void changePixelYOffset(int amt);
    //zoom functions
    void setSquareSize(int set);
    void changeSquareSize(int delta);
private:
    //members
    Square*** grid;
    int xPixelOffset,yPixelOffset;
    queue<pair<Terrain*,Square*> > terrainReplacementQu;
    queue<Thing*> occRemovalQu;
    queue<pair<Thing*,Square*> > occMovementQu;
public:
    void queueOccRemoval(Thing* remove);
    void queueTerrainReplacement(Terrain* replaceWith);

    //functions
    void movePixelOffsetsForScreenResize(int prevSQUARE_SIZE);
    void boundScreenSize();
    void adjustScreenForResize();
 

};

#endif	/* GRID_H */

