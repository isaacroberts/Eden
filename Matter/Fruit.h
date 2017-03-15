/* 
 * File:   Fruit.h
 * Author: Isaac
 *
 * Created on November 20, 2013, 2:54 PM
 */

#ifndef FRUIT_H
#define	FRUIT_H

#include "Mobador.h"
#include "Food.h"

class Fruit : public Mobador, public Food
{
public:
    Fruit(FruitType*);
    virtual ~Fruit();
    void update();
    joule getEdibleEnergy()const {
        return energy;
    }
    joule getAte(joule amt){
        Util::ensureBelow(amt,energy);
        energy-=amt;
        return amt;
    }
    joule getAte() {
        long eaten=energy;
        energy=0;
        return eaten;
    }
    FruitType* getFruitType()const 
    {
        return type;
    }
    ThingType* getType()const{
        return ThingType::Fruit_T;
    }
    Food::FoodGroup getFoodGroup()const {
        return Food::SeedFuel;
    }
    sizeval getSize()const{return SizeVal::Small;}
    void calcHeat();
    Color getColor()const;
    bool isDead()const;
    bool canSproutOn(Square* place)const;
    bool canSproutOn(TerrainType* type)const;
    virtual float height()const{return type->height;}
    virtual float surfaceArea()const {
        return 6.28*type->height;//2pi*Diameter
    }
    virtual float sideSurfaceArea()const{return type->height*.1;}
    virtual float volume()const{return type->volume;}
    virtual float getMass()const{return density()*volume();}
    virtual float density()const{return type->density;}
protected:
    void draw();
    void burn();
private:
    FruitType* type;
    joule energy;
    
};

#endif	/* FRUIT_H */

