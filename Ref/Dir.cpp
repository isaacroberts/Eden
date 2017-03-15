/* 
 * File:   Dir.cpp
 * Author: Isaac
 * 
 * Created on October 9, 2013, 11:42 AM
 */

#include "Dir.h"
#include "../World/Square.h"
#include "Util.h"

Dir* Dir::North;
Dir* Dir::East;
Dir* Dir::South;
Dir* Dir::West;

Dir* Dir::Down;

Dir* Dir::get(const Square* from,const Square* to)
{
    return get(Util::xDist(from->x(),to->x()),from->y()-to->y());
}