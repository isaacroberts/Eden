/* 
 * File:   Square.h
 * Author: Isaac
 *
 * Created on October 3, 2013, 8:01 PM
 */

#ifndef SQUARE_H
#define	SQUARE_H

#include <SDL.h>
#include <vector>
#include <queue>


/*
 * To solve circular dependencies, Square is forward declared in Thing.h
 * This means that nothing that includes Thing can have any refernce to
 * square other than pointers.
 * Square.h may only be included in cpp files, after Thing.h and ,<Classname>.h
 * 
 */

#include "../Matter/Sky.h"
#include "../Matter/Terrain.h"

#include "../Gui/Draw.h"
#include "../Ref/DisplayType.h"

using namespace std;


class Square
{
    friend class Grid;
    
    #define MAX_FREE_SPACE 10
public:
    static int squareSize;
    static int halfSquareSize;
    static int quarterSquareSize;
private:
    //members
    int gx,gy;//gridX & gridY
    int pixX,pixY;//pixelX & pixelY
    int hash;
    vector<Thing*> occs;//occupant: the thing in the square
    Terrain* terrain;
    Liquid* liquid;
    Sky* sky;
    byte redraw;
    sizeval freeSpace;
    //functions
    void deleteOccupant(int o);
    void deleteTerrain();
    void drawHumidity();
    Square();//error constructor
public:
    //functions
    Square(int x,int y);
    Square(const Square& orig);
    void finalizeConstruction();
    ~Square();
    void preStep();
    void update();
    void endStep();
    void draw();
    inline void fillRect() {
        Draw::rect(pixX,pixY,squareSize,squareSize);
    }
    inline void fillCircle() {
        Draw::circle(px()+halfSquareSize,py()+halfSquareSize,halfSquareSize-1);
    }
    inline void requireRedraw() {
        redraw=2;
    }
/*-------Thing Handling-------------*/
//Occupant
    //adding
    void addOccupant(Thing* add);
    void addOccupant(Thing* add,byte refAmt);
    //deletion
    bool removeOccupant(Thing* remove);
    void clearOccupant(int o);
    bool clearOccupant(Thing* remove);
    static void queueOccRemoval(Thing* remove);
    void queueOccRemoval(int o);
    
    void clearAllOccupants();
    //checking for occs
    bool hasOcc()const{return !occs.empty();}
    bool hasOccOfType(ThingType* type)const;
    bool hasOccOfTypes(ThingType* type,ThingType* type2)const;
    bool hasOccOfTypes(ThingType** typeArray,int typeAmt)const;
    Thing* getOccOfType(ThingType* type);
    int occAmt()const{return occs.size();}
    //space-based occing
    inline sizeval totalSpaceTaken()const {
        return MAX_FREE_SPACE-freeSpace;
    }
    inline sizeval getFreeSpace()const {
        return freeSpace;
    }
    Thing* getBiggestOcc();
//Terrain
    void installTerrain(Terrain* set);
    void setTerrain(Terrain* set);
    void clearTerrain();
    static void queueTerrainReplacement(Terrain* replacewith);
//Liquid
    void replaceLiquid(Liquid* replaceWith);
    bool requisitionWater(float amt);
    
/*--------Geographic Functions----------*/
    int neighborAmt()const;
    vector<Square*>* getNeighbors() const; 
    vector<Square*>* getOrdinalNeighbors() const;
    Square* randNeighbor()const;
    bool isNeighbor(Square* other)const;
    bool isOrdinalNeighbor(Square* other)const;
    inline Dir* getDir(const Square* to)const{return Dir::get(this,to);}
    //shifting
    inline Square* transform(Dir* by) const {return transform(by->x(),by->y());}
    Square* transform(int dx,int dy) const;
    Square* safeTransform(int dx,int dy)const;
    Square* transformCoord(coord& cx,coord& cy,int dx,int dy)const;
    Square* safeTranformCoord(coord& cx,coord& cy,int dx,int dy)const;
    //vector<Square*>* getSquareOfSquares(int radius);
/*---------Access Functions-------------*/
    inline Terrain* getTerrain() {  return terrain;   }
    inline Thing* getOccupant(int o){  return occs[o];  }
    inline Sky* getSky() {  return sky;  }
    inline Liquid* getLiquid(){return liquid;}
    //const accesses
    inline const Terrain* getTerrain() const{  return terrain;   }
    inline const Thing* getOccupant(int o)const{  return occs[o];  }
    inline const Sky* getSky() const{  return sky;  }
    inline const Liquid* getLiquid()const{return liquid;}
    //printing
    void printString() const;
    void printInfo()const;
    void printAmtsOfTypes()const;
    //basic grid functions
    inline int x() const {return gx;}
    inline int y() const {return gy;}
    inline int px() const {return pixX;}
    inline int py() const {return pixY;}
    inline int getHash()const{return hash;}
    inline bool equals(const Square* other)const{return gx==other->x() && gy==other->y(); }
    inline bool isnt(const Square* other) const{return gx!=other->x() || gy!=other->y(); }
    inline bool notError()const {return gx!=-1;}
    inline bool isError() const{return gx==-1;}

    static Square* getSquare(int x,int y);
};

#endif	/* SQUARE_H */

