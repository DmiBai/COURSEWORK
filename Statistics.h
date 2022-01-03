#pragma once
#include "Header.h"

class Statistics
{
    int mistakeNum;
    int keyPressed;
    double averageSpeed;
    int curMistakes;
    double accuracy;
    int time;
    double speed;
public:
    Statistics();

    Statistics(const Statistics&);

    void press();

    int getPressed();

    int getMistNum();

    void fKey();

    double getSpeed();

    double getAccuracy();

    void setTime(int);

    int getTime();

    void setPressed(int p);

    void setMistNum(int f);

    void nullAll();
};

