#include "main.h"
#include "ports.h"

#pragma once

class TwoBarTray {
public:
    Motor twoBar =  Motor(M_TWOBAR, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor tray = Motor(M_TRAY, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

private:
    bool twoBarManualMode = false;
    bool trayManualMode = false;

    ControllerButton twoBarUp = ControllerButton(C_TWOBAR_UP);
    ControllerButton twoBarDown = ControllerButton(C_TWOBAR_DOWN);
    ControllerButton trayUp = ControllerButton(C_TRAY_UP);
    ControllerButton trayDown = ControllerButton(C_TRAY_DOWN);

    ControllerButton intakePreset = ControllerButton(C_PRESET_INTAKE);
    ControllerButton stackPreset = ControllerButton(C_PRESET_STACK);

public:
    TwoBarTray();
    void update();
    void opcontrol();
    void moveToPreset(bool intake);
};
