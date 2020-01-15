#include "main.h"
#include "lift.h"
#include "ports.h"

enum class TrayPreset {
    stowed,
    intake,
    stack
};

class Tray {
private:
    Motor motor = Motor(M_TRAY, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
    Lift lift = Lift(&motor);

    ControllerButton stowedBtn = ControllerButton(C_TRAY_STOWED);
    ControllerButton stackBtn  = ControllerButton(C_TRAY_STACK);
    ControllerButton intakeBtn = ControllerButton(C_TRAY_INTAKE);
    ControllerButton upBtn     = ControllerButton(C_TRAY_UP);
    ControllerButton downBtn   = ControllerButton(C_TRAY_DOWN);

public:
    Tray();
    void opcontrol();
    void moveVelocity(int velocity);
    void moveToPreset(TrayPreset preset);
};
