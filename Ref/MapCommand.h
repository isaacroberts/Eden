/* 
 * File:   Click.h
 * Author: Isaac
 *
 * Created on October 7, 2013, 10:13 PM
 */  

#ifndef MAPCOMMAND_H
#define	MAPCOMMAND_H

#include <iostream>

class MapCommand
{
public:
    enum Type
    {
        AddWater,Dry,
        Still,Dehumidify,
        Heat,Cool,
        Mountain,Valley,
        Till,
        Tree,
        None//None must be last element for OOB checks
    };
    static bool isDragged(Type type)
    {
        switch (type)
        {
            case None:
            case Mountain:
            case Valley:
            case Tree:
                return false;
            case AddWater:
            case Dry:
            case Still:
            case Heat:
            case Cool:
            case Dehumidify:
            case Till:
                return true;
            default:
                std::cout<<"unrecognized Click::Type - "<<type<<" in isDragged()"<<std::endl;
                exit(0);
        }
    }
    static bool canBeGlobal(Type type)
    {
        return isDragged(type);
    }
//        switch(type)
//        {
//            case None:
//            case Mountain:
//            case Valley:
//                return false;
//            case AddWater:
//            case Dry:
//            case Still:
//            case Heat:
//            case Cool:
//                return true;
//            default:
//                std::cout<<"unrecognized Click::Type - "<<type<<" in canBeGlobal()"<<std::endl;
//                exit(0);
//        }
//    }
    static string getName(Type type)
    {
        switch(type)
        {
            case None:
                return "Cancel";
            case Mountain:
                return "Create Mountain";
            case Valley:
                return "Create Valley";
            case AddWater:
                return "Add Water";
            case Dry:
                return "Dry";
            case Still:
                return "Still Wind";
            case Heat:
                return "Heat";
            case Cool:
                return "Cool";
            case Dehumidify:
                return "Dehumidify";
            case Till:
                return "Turn to Dirt";
            case Tree:
                return "Make Tree";
            default:
                std::cout<<"unrecognized Click::Type - "<<type<<" in getName()\n";
                exit(0);
        }
    }
};

#endif	/* CLICK_H */

