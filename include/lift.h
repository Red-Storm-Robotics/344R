#include "main.h"

#pragma once

class Lift {
private:
    AbstractMotor* motor = NULL;
    bool manualMode = false;

public:
    Lift(AbstractMotor* motor);
    void moveVelocity(int rpm);
    void moveToPosition(int pos);
    void runNormally();
};
