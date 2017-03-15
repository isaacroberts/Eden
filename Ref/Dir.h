/* 
 * File:   Dir.h
 * Author: Isaac
 *
 * Created on October 9, 2013, 11:42 AM
 */

#ifndef DIR_H
#define	DIR_H

#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

#include "Util.h"
class Square;
using namespace std;
class Dir
{
private:
    short dx,dy;
    Dir(short xComponent,short yComponent)
    {
        dx=xComponent;
        dy=yComponent;
    }
    
public:
    inline short x()const {return dx;}
    inline short y()const {return dy;}
    std::string toString()const
    {
        if (dy==-1)
            return "North";
        else if (dx==1)
            return "East";
        else if (dy==1)
            return "South";
        else if (dx==-1)
            return "West";
        else if (dx==0 && dy==0)
            return "Down";
        else return "Unrecognized direction";
    }
    Dir* rotate(bool clockwise)const
    {
        short rotY=dx;
        short rotX=dy;
        if (clockwise)
            rotX*=-1;
        else 
            rotY*=-1;
        return certainGet(rotX,rotY);
    }
    Dir* rotateClockwise()const
    {
        return certainGet(-dy,dx);
    }
    Dir* rotateAntiClockwise()const
    {
        return certainGet(dy,-dx);
    }
    inline Dir* opposite()const 
    {
        return certainGet(-dx,-dy);
    }
    inline bool equals(Dir* other)const
    {
        return (dx==other->dx && dy==other->dy);
    }
public:
    static Dir *North,*East,*South,*West, *Down;
    static void initialize()
    {
        North=new Dir(0,-1);
        East=new Dir(1,0);
        South=new Dir(0,1);
        West=new Dir(-1,0);
        Down=new Dir(0,0);
    }
    static Dir* certainGet(short x,short y)
    {
        if (x==0)
        {
            if (y==-1)
                return North;
            else return South;
        }
        else if (x==1)
            return East;
        else return West;
    }
    static Dir* get(int x,int y)
    {
        if (abs(y)>abs(x))
        {
            if (y>0)
                return South;
            else return North;
        }
        else
        {
            if (x>0)
                return East;
            else if (x<0)
                return West;
            else return Down;
        }
    }
    static Dir* getDir(int id)
    {
        switch (id)
        {
            case 0: return North;
            case 1: return East;
            case 2: return South;
            case 3: return West;
            default: 
                cout<<"Invalid id in getDir(int) : "<<id<<endl;
                return Down;
        }
    }
    static Dir* getRandDir()
    {
        return getDir(rand()%4);
    }
    static vector<Dir*> getDirVector() {
        vector<Dir*> dirs=vector<Dir*>();
        dirs.push_back(North);
        dirs.push_back(East);
        dirs.push_back(South);
        dirs.push_back(West);
        return dirs;
    }
    static Dir* get(const Square* from,const Square* to);
};

#endif	/* DIR_H */

