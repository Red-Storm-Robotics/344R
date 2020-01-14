#include "main.h"

#pragma once

class Lift {
private:
    AbstractMotor* motor = NULL;
    bool manualMode = false;

public:
    int presets[5];

    Lift(AbstractMotor* motor);
    void moveVelocity(int rpm);
    void moveToPreset(int preset);
    void runNormally();
};
