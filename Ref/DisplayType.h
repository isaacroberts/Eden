/* 
 * File:   DisplayType.h
 * Author: Isaac
 *
 * Created on January 18, 2014, 1:38 PM
 */

#ifndef DISPLAYTYPE_H
#define	DISPLAYTYPE_H

#include <iostream>
using namespace std;
class DisplayType {
public:
    enum Type
    {
        Loading,Normal,
        Elevation,WaterFlow,
        Heat,Humidity,
        AirMass,Wind

    };
    //the types that can be selected by the player
    static const Type selectable[];
    static const int selectableAmt;
    static bool showsTerrain(Type type);
    static bool showsOccupants(Type type);
    static string getName(Type);
};
extern DisplayType::Type displayType;
#endif	/* DISPLAYTYPE_H */

