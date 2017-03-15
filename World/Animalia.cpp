/* 
 * File:   Animalia.cpp
 * Author: Isaac
 * 
 * Created on February 22, 2014, 1:43 AM
 */

#include "Animalia.h"

vector<Species*> Animalia::kingdom;
Species* Animalia::gerbil;
void Animalia::originOfSpecies()
{
    kingdom=vector<Species*>();
    gerbil=new Species();
    gerbil->bloodRegen=.005;
    gerbil->metabolism=3;
    gerbil->maxBlood=1;
    gerbil->maxEnergy=1000;
    
    
}
    