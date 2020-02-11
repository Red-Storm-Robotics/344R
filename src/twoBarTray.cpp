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
        moveToPreset(P_INTK_NUM);
    } else if (stackPreset.changedToPressed()) {
        moveToPreset(P_STACK_NUM);
    } else if (lowPreset.changedToPressed()) {
        moveToPreset(P_LOW_NUM);
    } else if (midPreset.changedToPressed()) {
        moveToPreset(P_MID_NUM);
    }
}



void TwoBarTray::moveToPreset(int preset) {
    twoBarManualMode = false;
    trayManualMode = false;

    if (preset == P_INTK_NUM) {
        twoBar.moveAbsolute(P_TWOBAR_INTAKE, 100);
        tray.moveAbsolute(P_TRAY_INTAKE, 100);
    } else if (preset == P_STACK_NUM) {
        twoBar.moveAbsolute(P_TWOBAR_STACK, 75);
        tray.moveAbsolute(P_TRAY_STACK, 75);
    } else if (preset == P_LOW_NUM) {
       twoBar.moveAbsolute(P_TWOBAR_LOW, 100);
       tray.moveAbsolute(P_TRAY_TOWER, 100);
    } else if (preset == P_MID_NUM) {
      twoBar.moveAbsolute(P_TWOBAR_MID, 100);
      tray.moveAbsolute(P_TRAY_TOWER, 100);
    }
}
