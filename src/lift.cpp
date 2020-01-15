#include "main.h"
#include "lift.h"

Lift::Lift(AbstractMotor* imotor) {
    motor = imotor;
    motor->setBrakeMode(AbstractMotor::brakeMode::hold);
};

void Lift::moveVelocity(int rpm) {
    manualMode = true;
    motor->moveVelocity(rpm);
}

void Lift::moveToPosition(int pos) {
    manualMode = false;
    motor->moveAbsolute(pos, 200);
}

void Lift::runNormally() {
    if (manualMode) {
        motor->moveVelocity(0);
    }
}
