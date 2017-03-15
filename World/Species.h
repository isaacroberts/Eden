/* 
 * File:   Species.h
 * Author: Isaac
 *
 * Created on February 22, 2014, 1:09 AM
 */

#ifndef SPECIES_H
#define	SPECIES_H

class Species {
public:
    friend class Animalia;
    
    Species();
    Species(const Species& orig);
    virtual ~Species();
protected:
    double metabolism;//joules spent per update
    double bloodRegen;//blood gained per update
    float maxBlood;
    float maxEnergy;
public:
/*------Access Functions---------*/
    //nonvariable
    //inlines
    inline double getMetabolism() const{
        return metabolism;
    }
    inline double getBloodRegen() const{
        return bloodRegen;
    }
    inline float getMaxEnergy() const{
        return maxEnergy;
    }
    inline float getMaxBlood() const{
        return maxBlood;
    }
    
    
};

#endif	/* SPECIES_H */

