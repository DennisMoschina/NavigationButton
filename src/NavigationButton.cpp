#include <Arduino.h>
#include "NavigationButton.h"

NavigationButton::NavigationButton(byte pin) {
    this->pin = pin;

    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), interacted, CHANGE);
}

void NavigationButton::interacted() {
    if (!digitalRead(pin)) {
      this->pressed = millis();
    } else {
        this->released = millis();

        if (checkForLongPress) {
            this->longPressAction[longPressCounter];

            this->longPressCounter =
                (longPressCounter + 1) % this->longPressAction.size();
        } else {
            this->shortPressAction[shortPressCounter];

            this->shortPressCounter =
                (shortPressCounter + 1) % this->shortPressAction.size();
        }
    }
}

bool checkForLongPress() {
  int difference = this->released - this->pressed;
  return (difference) > longPressTime;
}

void NavigationButton::addLongPressAction(std::function<void()> action) {
    this->longPressAction.push_back(action);
}
void addShortPressAction(std::function<void()> action) {
    this->shortPressAction.push_back(action);
}
void NavigationButton::setLongPressCounter(int counter) {
    this->longPressCounter = counter;
}

void NavigationButton::setShortPressCounter(int counter) {
    this->shortPressCounter = counter;
}
