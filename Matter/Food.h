/* 
 * File:   Food.h
 * Author: Isaac
 *
 * Created on March 8, 2014, 1:34 AM
 */

#ifndef FOOD_H
#define	FOOD_H

#include "Thing.h"

class Food : public virtual Thing
{
public:
    virtual ~Food();
    
    enum FoodGroup
    {
        Meat,SeedFuel/*Fruit/Veg/Nuts*/,
        OtherPlant,
    };
    
    virtual joule getEdibleEnergy()const=0;//in joules
    virtual joule getAte(joule amount)=0;
    virtual joule getAte()=0;
    virtual FoodGroup getFoodGroup()const=0;
    
private:

};

#endif	/* FOOD_H */

