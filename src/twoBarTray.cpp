#include "main.h"
#include "ports.h"
#include "twoBarTray.h"

TwoBarTray::TwoBarTray() {
    twoBar.setBrakeMode(AbstractMotor::brakeMode::hold);
    tray.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void TwoBarTray::update() {

}

void TwoBarTray::opcontrol() {
    if (twoBarUp.isPressed()) {
        twoBar.moveVelocity(100);
        twoBarManualMode = true;
    } else if (twoBarDown.isPressed()) {
        twoBar.moveVelocity(-100);
        twoBarManualMode = true;
    } else if (twoBarManualMode) {
        twoBar.moveVelocity(0);
    }

    if (trayUp.isPressed()) {
        tray.moveVelocity(100);
        trayManualMode = true;
    } else if (trayDown.isPressed()) {
        tray.moveVelocity(-100);
        trayManualMode = true;
    } else if (trayManualMode) {
        tray.moveVelocity(0);
    }

    if (intakePreset.changedToPressed()) {
        moveToPreset(true);
    } else if (stackPreset.changedToPressed()) {
        moveToPreset(false);
    }
}

void TwoBarTray::moveToPreset(bool intake) {
    twoBarManualMode = false;
    trayManualMode = false;

    if (intake) {
        twoBar.moveAbsolute(P_TWOBAR_INTAKE, 100);
        tray.moveAbsolute(P_TRAY_INTAKE, 100);
    } else {
        twoBar.moveAbsolute(P_TWOBAR_STACK, 100);
        tray.moveAbsolute(P_TRAY_STACK, 100);
    }
}
