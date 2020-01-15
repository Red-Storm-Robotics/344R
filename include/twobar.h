#include "main.h"
#include "lift.h"
#include "ports.h"

enum class TwoBarPreset {
    stowed,
    intake,
    lowTower,
    midTower
};

class TwoBar {
private:
    Motor motor = Motor(M_TWOBAR, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Lift lift = Lift(&motor);

    //ControllerButton stowedBtn = ControllerButton(C_TWOBAR_STOWED);
    ControllerButton lowTowerBtn  = ControllerButton(C_TWOBAR_LOW_TOWER);
    ControllerButton midTowerBtn = ControllerButton(C_TWOBAR_MID_TOWER);
    ControllerButton intakeBtn = ControllerButton(C_TWOBAR_INTAKE);
    ControllerButton upBtn     = ControllerButton(C_TWOBAR_UP);
    ControllerButton downBtn   = ControllerButton(C_TWOBAR_DOWN);

public:
    TwoBar();
    void opcontrol();
    void moveVelocity(int velocity);
    void moveToPreset(TwoBarPreset preset);
};
