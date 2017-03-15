/* 
 * File:   Dirt.h
 * Author: Isaac
 *
 * Created on October 5, 2013, 1:37 PM
 */

#ifndef DIRT_H
#define	DIRT_H

#include "../World/Square.h"//i do not like this
#include "Terrain.h"
#include "Lava.h"
#include "../Ref/Type.h"

using namespace std;

class Dirt : public Terrain
{
    public:
        Dirt()
        {
            construct();
        }
        virtual TerrainType* getType() const
        {
            return ThingType::Dirt_T;
        }
        Color getColor()const {
             if (burning())
                return Color(Color::colorBound(130+(heat-getType()->flashPoint)/5),75,25);
            else
                return *getType()->color;
        }
        inline virtual long saturation() {return getType()->saturation; }
    protected:
        virtual void update(){}
        virtual void burn()
        {
            if (heat<getFlashPoint()+700)
                loc->requireRedraw();
            /*
            float rockMelt=(heat-getFlashPoint())/100.0;
            if (loc->getLiquid()->getLiquidType()==LiquidType::Lava_T)
            {
                addLandMass(-rockMelt);
                loc->getLiquid()->addAndSatMass(rockMelt);
            }
            else if (!loc->getLiquid()->submerged())
            {
                float sat=loc->getLiquid()->mainLiquidMass();
                loc->replaceLiquid(new Lava());
                loc->getLiquid()->setSaturatedMass(sat);
                addLandMass(-rockMelt);
                loc->getLiquid()->addAndSatMass(rockMelt);
            }
            */
        }
    private:
};

#endif	/* DIRT_H */

