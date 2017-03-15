/* 
 * File:   LoadingScreen.h
 * Author: Isaac
 *
 * Created on October 10, 2013, 5:53 PM
 */

#ifndef LOADINGSCREEN_H
#define	LOADINGSCREEN_H

#include <string>

#include "../Ref/Util.h"

using namespace std;

class LoadingScreen {
public:
    enum Task
    {
        Setup,Square,Mountains,Spring,Occupants,Forest
    };
    LoadingScreen();
    void display();
    inline void setPercentage(float current,float outOf) 
        {percentage=current/outOf;display();}
    inline void setPercentage(float set) {
        percentage=set;display();  }
    void setTask(Task set);
    void setCurrent(float setPercent,Task setTask);

    static string getMessage(Task task);
    string getCurMessage() {
        return getMessage(task);
    }
private:
    byte taskChanged;
    float percentage;
    Task task;
};

#endif	/* LOADINGSCREEN_H */

