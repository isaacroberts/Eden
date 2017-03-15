/* 
 * File:   Spring.h
 * Author: Isaac
 *
 * Created on October 18, 2013, 7:20 PM
 */

#ifndef SPRING_H
#define	SPRING_H

#include "Terrain.h"

class Spring : public Terrain
{
public:
    static long springFlow;
    Spring() {
        Terrain::construct();
    }
    void update();
    virtual TerrainType* getType() const{
        return ThingType::Spring_T;
    }
    virtual void paintNormal() {
        draw();
    }
protected:
    void burn(){}
};
#endif	/* SPRING_H */

