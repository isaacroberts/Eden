/* 
 * File:   Size.h
 * Author: Isaac
 *
 * Created on March 12, 2014, 5:10 PM
 */

#ifndef SIZE_H
#define	SIZE_H

#include "Util.h"

typedef short int sizeval;

namespace SizeVal {
    extern sizeval Tiny,Small,Medium;
    extern sizeval Large,Huge;
    
    /*v
     * The Value of the sizevals of objects in the square
     * Cannot exceed 10.
     * 
     * Tiny Things are ignored in terms of taking up space
     * Small Things can share a square with 9 other smalls
     * Medium Things can share a square with One other medium
     * Large Things can not share a square with medium objects
     * Huge Things can not share a square with even small objects
     */
}


#endif	/* SIZE_H */

