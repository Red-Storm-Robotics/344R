#include "main.h"
#include "twobar.h"

TwoBar::TwoBar() {

}

void TwoBar::moveVelocity(int velocity) {
    lift.moveVelocity(velocity);
}

void TwoBar::moveToPreset(TwoBarPreset preset) {
    switch (preset) {
        case TwoBarPreset::stowed: {
            lift.moveToPosition(P_TWOBAR_STOWED);
        }
        case TwoBarPreset::intake: {
            lift.moveToPosition(P_TWOBAR_INTAKE);
        }
        case TwoBarPreset::lowTower: {
            lift.moveToPosition(P_TWOBAR_LOW_TOWER);
        }
        case TwoBarPreset::midTower: {
            lift.moveToPosition(P_TWOBAR_MID_TOWER);
        }
    }
}

void TwoBar::opcontrol() {
    if (intakeBtn.changedToPressed()) {
        moveToPreset(TwoBarPreset::intake);
    } else if (lowTowerBtn.changedToPressed()) {
        moveToPreset(TwoBarPreset::lowTower);
    } else if (midTowerBtn.changedToPressed()) {
        moveToPreset(TwoBarPreset::midTower);
    } else if (upBtn.isPressed()) {
        moveVelocity(200);
    } else if (downBtn.isPressed()) {
        moveVelocity(-200);
    } else {
        lift.runNormally();
    }
}
