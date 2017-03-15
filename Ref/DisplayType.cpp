
#ifndef DISPLAY_TYPE_CPP
#define DISPLAY_TYPE_CPP

#include "DisplayType.h"

using namespace std;

const DisplayType::Type DisplayType::selectable[]={Normal,Elevation,WaterFlow,Heat,Humidity,AirMass,Wind};
const int DisplayType::selectableAmt=7;
bool DisplayType::showsTerrain(Type type)
{
    switch (type)
    {
        case Loading:
        case Humidity:
        case AirMass:
        case Wind:
        case Heat:
            return false;
        case Normal:
        case Elevation:
        case WaterFlow:
            return true;
    }
    cout<<"displayType::ShowsTerrain function not complete"<<endl;
}
bool DisplayType::showsOccupants(Type type)
{
    switch (type)
    {
        case Normal:
            return true;
        case Loading:
        case Elevation:
        case WaterFlow:
        case Heat:
        case Humidity:
        case AirMass:
        case Wind:
            return false;
    }
    cout<<"displayType::ShowsOccupants function not complete"<<endl;
}
string DisplayType::getName(Type type)
{
    switch (type)
    {
        case Normal:
            return "Map";
        case Loading:
            return "Loading Screen";
        case Elevation:
            return "Elevation";
        case WaterFlow:
            return "Water Flow";
        case Heat:
            return "Heat Map";
        case Humidity:
            return "Humidity";
        case AirMass:
            return "Density";
        case Wind:
            return "Wind Speed";
        default:
            cout<<"Error: DisplayType::getName() not completed\n";
            exit(0);
    }
}

#endif
