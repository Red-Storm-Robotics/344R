#include "main.h"
#include "ports.h"
#include "intake.h"

Intake::Intake() {
    motor.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void Intake::update() {
    switch (state) {
        case IntakeState::forward:
            motor.moveVelocity(200);
            break;
        case IntakeState::stop:
            motor.moveVelocity(0);
            break;
        case IntakeState::reverse:
            motor.moveVelocity(-150);
            break;
    }
}

void Intake::switchToState(IntakeState istate) {
    state = istate;
    update();
}

void Intake::opcontrol() {
    pros::lcd::print(6, "%d", (int)state);
    if (state == IntakeState::forward) {
        if (forwardBtn.changedToPressed()) {
            state = IntakeState::stop;
        } else if (reverseBtn.changedToPressed()) {
            state = IntakeState::reverse;
        }
    } else if (state == IntakeState::reverse) {
        if (reverseBtn.changedToPressed()) {
            state = IntakeState::stop;
        } else if (forwardBtn.changedToPressed()) {
            state = IntakeState::forward;
        }
    } else {
        if (forwardBtn.changedToPressed()) {
            state = IntakeState::forward;
        } else if (reverseBtn.changedToPressed()) {
            state = IntakeState::reverse;
        }
    }
    update();
}
