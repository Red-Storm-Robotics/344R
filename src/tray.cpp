#include "main.h"
#include "tray.h"

Tray::Tray() {

}

void Tray::moveVelocity(int velocity) {
    lift.moveVelocity(velocity);
}

void Tray::moveToPreset(TrayPreset preset) {
    switch (preset) {
        case TrayPreset::stowed: {
            lift.moveToPosition(P_TRAY_STOWED);
        }
        case TrayPreset::intake: {
            lift.moveToPosition(P_TRAY_INTAKE);
        }
        case TrayPreset::stack: {
            lift.moveToPosition(P_TRAY_STACK);
        }
    }
}

void Tray::opcontrol() {
    if (stowedBtn.changedToPressed()) {
        moveToPreset(TrayPreset::stowed);
    } else if (stackBtn.changedToPressed()) {
        moveToPreset(TrayPreset::stack);
    } else if (intakeBtn.changedToPressed()) {
        moveToPreset(TrayPreset::intake);
    } else if (upBtn.isPressed()) {
        moveVelocity(100);
    } else if (downBtn.isPressed()) {
        moveVelocity(-100);
    } else {
        lift.runNormally();
    }
}
