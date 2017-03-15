
#include "Spring.h"
#include "../World/Square.h"


void Spring::update()
{
    loc->getLiquid()->changeMass(springFlow);
//    if (Util::time()%100 < 30) {
//        loc->getLiquid()->giveLiquid(10000,LiquidType::Blood_T);
//    }
}