#ifndef _NAVIGATION_BUTTON_H
#define _NAVIGATION_BUTTON_H

#include <Arduino.h>

#include <vector>
#include <functional>

class NavigationButton {
public:
    NavigationButton(byte pin, int longPressTime = 1000);

    void setLongPressTime(int longPressTime);

    void addLongPressAction(std::function<void()> action);
    void addShortPressAction(std::function<void()> action);

    void setLongPressCounter(int counter = 0);
    void setShortPressCounter(int counter = 0);
    
    void interacted();

private:
    byte pin;

    int longPressCounter;
    int shortPressCounter;

    unsigned long pressed;
    unsigned long released;

    int longPressTime;

    std::vector<std::function<void()>> longPressAction;
    std::vector<std::function<void()>> shortPressAction;

    boolean checkForLongPress();
};

#endif
