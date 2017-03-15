/* 
 * File:   Lava.h
 * Author: Isaac
 *
 * Created on November 15, 2013, 1:03 PM
 */

#ifndef LAVA_H
#define	LAVA_H
#include "Liquid.h"

class Lava : public Liquid
{
public:
    Lava();
    Lava* clone()const;
    LiquidType* getLiquidType()const{return LiquidType::Lava_T;}
    void update();
    Color::hue colorAlpha()const;
    Lava(const Lava& orig);
    virtual ~Lava();
private:

};

#endif	/* LAVA_H */

