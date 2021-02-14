#include <Arduino.h>
#include "NavigationButton.h"


NavigationButton* pointerToClassNB;

static void outsideInteracted() {
  pointerToClassNB->interacted();
}


NavigationButton::NavigationButton(byte pin, int longPressTime) {
    this->pin = pin;
    this->longPressTime = longPressTime;

    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), outsideInteracted, CHANGE);
}

void NavigationButton::setLongPressTime(int longPressTime) {
    this->longPressTime = longPressTime;
}

void NavigationButton::interacted() {
    if (!digitalRead(pin)) {
      this->pressed = millis();
    } else {
        this->released = millis();

        if (checkForLongPress()) {
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

bool NavigationButton::checkForLongPress() {
  int difference = this->released - this->pressed;
  return (difference) > longPressTime;
}

void NavigationButton::addLongPressAction(std::function<void()> action) {
    this->longPressAction.push_back(action);
}
void NavigationButton::addShortPressAction(std::function<void()> action) {
    this->shortPressAction.push_back(action);
}
void NavigationButton::setLongPressCounter(int counter) {
    this->longPressCounter = counter;
}

void NavigationButton::setShortPressCounter(int counter) {
    this->shortPressCounter = counter;
}
