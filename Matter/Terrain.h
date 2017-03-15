/* 
 * File:   Terrain.h
 * Author: Isaac
 *
 * Created on October 4, 2013, 1:08 PM
 */

#ifndef TERRAIN_H
#define TERRAIN_H

#include "Thing.h"
#include "Liquid.h"

class Terrain : virtual public Thing
{
    
public:
    //doing functions
    Terrain();
    Terrain(const Terrain& orig);
    virtual Terrain* clone()const;
    virtual void replace(Terrain* orig);
    void makePropertiesSameAs(const Terrain* change);
    void construct();
    virtual ~Terrain();
    void paint();
    virtual void preStep();
    virtual void endStep();
    //setters
/*pure*/virtual TerrainType* getType()const=0;
    inline void changeElevation(float amt) {elevation+=amt;}
    inline void addLandMass(float amt){elevation+=amt/density();}
    inline void setElevation(float set){elevation=set;}
    virtual void erode(float amt){elevation-=amt;}
    
    void setLoc(Square* set);
    //accessors
    sizeval getSize()const{return 0;}
    bool underwater()const;
    float volume()const{return 5;}//assuming only 5m down is affected
    long waterAbove()const;
    float metersOfWaterAbove()const;
    float altitude()const;
    virtual float surfaceArea()const{return 1;}
    inline float getElevation()const{return elevation;}
    float getSlope(Dir* dir)const;
    virtual float height()const{return elevation;}
    void printInfo()const;
    static int elevationDrawSlope;
    //terrain type accessors : overridable to allow for
        // dynamic or object-dependant values
    virtual kilogram saturation()const;
    virtual float getSunReceptivity()const;
    virtual float getCoeffFriction()const;
    //abstract identifiers
    virtual bool isCovering(){return false;}
    bool isAllocated()const{return true;}
protected:
    float elevation;
    //doing functions
    void handlePhysics();
    virtual void handleErosion();
    void calcHeat();
    virtual void checkForBurn();
    void exchangeHeat(Square* with,float rate);
    virtual void paintNormal();
    virtual void draw();
private:
    void drawElevation();   
    void drawHeat();
    
};

#endif	/* TERRAIN_H */

