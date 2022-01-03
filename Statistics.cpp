#include "Statistics.h"

Statistics::Statistics() {
    mistakeNum = 0;
    keyPressed = 0;
    curMistakes = 0;
    speed = 1;
    accuracy = 1;
    time = 1;
}

Statistics::Statistics(const Statistics& obj) {
    mistakeNum = obj.mistakeNum;
    keyPressed = obj.keyPressed;
    averageSpeed = obj.averageSpeed;
    curMistakes = obj.curMistakes;
    accuracy = obj.accuracy;
    time = obj.time;
}

void Statistics::press() {
    keyPressed++;
}

int Statistics::getPressed() {
    return keyPressed;
}

int Statistics::getMistNum() {
    return mistakeNum;
}

void Statistics::fKey() {
    mistakeNum++;
}

double Statistics::getSpeed() {
    speed = keyPressed * 100 / time / 100.0;
    return speed;
}

double Statistics::getAccuracy() {
    accuracy = 100.0 - (mistakeNum * 100 / keyPressed);
    return accuracy;
}

void Statistics::setTime(int _time) {
    time = _time;
    return;
}

int Statistics::getTime() {
    return time;
}

void Statistics::setPressed(int p) {
    keyPressed = p;
}

void Statistics::setMistNum(int f) {
    mistakeNum = f;
}

void Statistics::nullAll() {
    mistakeNum = 0;
    keyPressed = 0;
    curMistakes = 0;
    speed = 1;
    accuracy = 1;
}