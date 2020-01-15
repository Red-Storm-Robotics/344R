#include "main.h"
#include "ports.h"

enum class IntakeState {
    forward,
    stop,
    reverse
};

class Intake {
private:
    IntakeState state = IntakeState::stop;
    ControllerButton forwardBtn = ControllerButton(C_INTAKE_FWD);
    ControllerButton reverseBtn = ControllerButton(C_INTAKE_REV);
    MotorGroup motor = MotorGroup({M_INTAKE_L, M_INTAKE_R});

public:
    Intake();
    void opcontrol();
    void switchToState(IntakeState istate);
    void update();
};
