/* 
 * File:   Animal.h
 * Author: Isaac
 *
 * Created on February 19, 2014, 12:44 PM
 */

#ifndef ANIMAL_H
#define	ANIMAL_H

#include "Mobador.h"
#include "../World/Species.h"
#include "Food.h"

class Animal : public Mobador, public Food
{
public:
    Animal(Species* setSpecies);
    Animal(const Animal& orig);
    virtual ~Animal();
/*--------Doing-----------------*/
    //per-update calls
    virtual void preStep();
    virtual void endStep();
protected:
    virtual void update();
    virtual void burn();
    virtual void draw();
    void drawStatusBars();
    //animally things
    virtual void hit(double force,double area);//newtons,m^2
    //overridable functions
    virtual void metabolize();
    virtual void digest(float energy);
    //virtual void accelerate() maybe override for 'g force' injuries and shit
    //food things
    FoodGroup getFoodGroup()const {
        return Food::Meat;
    }
    joule getEdibleEnergy() const{
        return energy;
    }
    joule getAte(joule amt){return amt;}
    joule getAte(){return energy;}
/*--------Info-------------*/
    ThingType* getType()const {
        return ThingType::Animal_T;
    }
    //complex
    virtual bool isDead()const;
    virtual void printInfo()const;
    //dimensionals
    sizeval getSize()const{return SizeVal::Medium;}
    virtual float height()const;//meters
    virtual float surfaceArea()const;//square meters
//    virtual float sideSurfaceArea()const{return height();}
//    virtual float volume()const{return height();}
//    virtual float getMass()const{return density()*volume();}
//    virtual float density()const{return getType()->density;}

protected:
    float energy;//joules
            //an apple has 500 joules
    float blood;//kilograms
            //a human has ~5 kg of blood
    Species* species;

public:
/*-----Access Functions------*/
    inline float getEnergy()const{
        return energy;
    }
    inline float getBlood() const{
        return blood;
    }
    inline const Species* getSpecies()const{
        return species;
    }
    inline Species* getSpecies() {
        return species;
    }
};

#endif	/* ANIMAL_H */

