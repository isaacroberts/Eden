/* 
 * File:   Animalia.h
 * Author: Isaac
 *
 * Created on February 22, 2014, 1:43 AM
 */

#ifndef ANIMALIA_H
#define	ANIMALIA_H

#include <vector>

#include "Species.h"

using namespace std;

class Animalia
{
public:
    static vector<Species*> kingdom;
    static Species* gerbil;
    static void originOfSpecies();
};

#endif	/* ANIMALIA_H */

