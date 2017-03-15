/* 
 * File:   Roots.h
 * Author: Isaac
 *
 * Created on December 13, 2013, 5:58 PM
 */

#ifndef ROOTS_H
#define	ROOTS_H

#include "Covering.h"
#include "Plant.h"

class Roots : public Plant
{
    /*
     In Roots, length measures how far across the ground
     * the roots extend in centimeters
     * 
     * 
     *   length=60
     * |----------|
     * __________________
     * | -              |
     * | /     /---     |
     * |-\---<          |
     * | /   / |        |
     * |\--\            |
     * | /  \           |
     * |/   /           |
     * |                |
     * |________________|
     * 
     * Reproduction length is 100, meaning the roots
     * extend all the way across the square
     * and can extend to the next square
     */
public:
    Roots();
    Roots(Plant* setParent);
//    virtual void replace(Terrain* other);
    virtual ~Roots();//find & orphanize children
    Roots* clone()const;
    virtual ThingType* getType()const {
        return ThingType::Roots_T;
    }
    virtual bool requisitionWater(float amt);
    void update();
    void printInfo()const;
    bool canGrow()const;
    bool canReproduce()const;
    inline void orphanize() {
        parent=NULL;
    }
    sizeval getSize()const{return SizeVal::Tiny;}
    float height()const {
        return .02;
    }
    float surfaceArea()const {
        return length *.03;//based on guesses
    }
    float sideSurfaceArea()const{return .1;}
    virtual float heatToLengthRatio() {
        return 0;
    }
    virtual float moistureToLengthRatio() {
        return 4;
    }
    inline Plant* getParent() {
        return parent;
    }
    inline void setParent(Plant* set) {
        parent=set;
    }
    bool canGrowOn(TerrainType* type)const;
    bool reproduce();
    int spawnDescendants(int amt);
    bool forceReproduce();
    void draw();
    Plant* getAncestor()const {
        if (parent==NULL || parent->isDead())
            return NULL;
        else if (parent->isA(ThingType::Roots_T))
        {
            return dynamic_cast<Roots*>
                    (parent)->getAncestor();
        }
        else
            return parent;
    }
    bool isRelated(const Roots* other)const{
        return areEqual(getAncestor(),other->getAncestor());
    }
protected:
    void burn();
    Plant* parent;
    float moisture;//in kg
};

#endif	/* ROOTS_H */

