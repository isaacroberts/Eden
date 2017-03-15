/* 
 * File:   Tree.h
 * Author: Isaac
 *
 * Created on October 28, 2013, 2:48 PM
 */



#ifndef TREE_H
#define	TREE_H

#include "Plant.h"
#include "Roots.h"

class Tree : public Plant
{
public:
    Tree();
    Tree(FruitType* setFruitType);
    Tree(FruitType* setFruitType,int setHeight);
    Tree(FruitType* setFruitType,int setHeight,Roots* setRoots);
    void construct();
    Tree* clone()const;
    virtual ~Tree();
    //doing
    virtual Color burnColor() const{
        return Color(250,100,0);
    }
    void setLoc(Square* set);
    int heightAlpha() {  return Color::colorBound(length/20); }
    virtual void printInfo()const;
    virtual bool reproduce();
    inline void setFruitAmt(byte set) {
        fruitAmt=set;
    }
    void update();
    void draw();
    inline void setRoots(Roots* set) {
        roots=set;
        roots->setParent(this);
        roots->addRef();
    }
    inline void clearRoots() {
        roots=NULL;
    }
    //accessors
    virtual bool canGrow()const;
    virtual bool canReproduce()const;
    virtual float heatToLengthRatio() {
        return 0;
    }
    virtual float moistureToLengthRatio() {
        return 1;
    }
    sizeval getSize()const{return SizeVal::Large;}
    virtual float surfaceArea()const {
        return length*0.0314;//length(cm)/100(cm/m) * pi
    }
    virtual float getCalories();
    virtual ThingType* getType()const {
        return ThingType::Tree_T;
    }
    inline Roots* getRoots(){return roots;}
    inline const Roots* getRoots()const{return roots;}
protected:
    virtual void burn();
        
    FruitType* fruitType;
    byte fruitAmt;
    Roots* roots;
private:
};

#endif	/* TREE_H */

