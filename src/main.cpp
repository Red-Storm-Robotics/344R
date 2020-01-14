#include "main.h"
#include "lift.h"

Controller controller;

auto chassis = ChassisControllerBuilder()
                .withMotors(1, 9, -2, -10)
                .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
                .build();

MotorGroup intakeMotors = MotorGroup({3, -8});

// INTAKE
ControllerButton intakeFwd(ControllerDigital::L1);
ControllerButton intakeRev(ControllerDigital::L2);

// TRAY
Motor trayMotor(5, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
Lift tray(&trayMotor);

ControllerButton trayBack(ControllerDigital::Y);
ControllerButton trayForward(ControllerDigital::X);

ControllerButton trayStowed(ControllerDigital::left);
ControllerButton trayIntaking(ControllerDigital::R2);
ControllerButton trayStacking(ControllerDigital::R1);

// TWO BAR
Motor twoBarMotor(6, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Lift twoBar(&twoBarMotor);

ControllerButton twoBarUp(ControllerDigital::up);
ControllerButton twoBarDown(ControllerDigital::right);

ControllerButton twoBarIntaking(ControllerDigital::down);
ControllerButton twoBarLowTower(ControllerDigital::B);
ControllerButton twoBarMidTower(ControllerDigital::A);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
    pros::lcd::set_text(0, "344R code, built on:");
	pros::lcd::set_text(1, __DATE__);
    pros::lcd::set_text(2, __TIME__);

    intakeMotors.setBrakeMode(AbstractMotor::brakeMode::hold);

    tray.presets[0] = 0; // Stowed
    tray.presets[1] = 90; // Intaking
    tray.presets[2] = 180; // Stacking

    twoBar.presets[0] = 0; // Stowed
    twoBar.presets[1] = 90; // Intaking
    twoBar.presets[2] = 180; // Low Tower
    twoBar.presets[3] = 360; // Mid Tower
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    chassis->moveDistance(24_in);
    chassis->waitUntilSettled();
    pros::delay(1000);
    chassis->moveDistance(-24_in);
    chassis->waitUntilSettled();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	while (true) {
        int speed = controller.getAnalog(ControllerAnalog::leftY);
        int steer = controller.getAnalog(ControllerAnalog::rightX);

        chassis->getModel()->arcade(speed, steer);

        // INTAKE

        if (intakeFwd.isPressed()) {
            intakeMotors.moveVelocity(200);
        } else if (intakeRev.isPressed()) {
            intakeMotors.moveVelocity(-200);
        } else {
            intakeMotors.moveVelocity(0);
        }

        // TRAY

        if (trayBack.isPressed()) {
            tray.moveVelocity(-100);
        } else if (trayForward.isPressed()) {
            tray.moveVelocity(100);
        } else {
            tray.runNormally();
        }

        if (trayStowed.changedToPressed()) {
            tray.moveToPreset(0);
        } else if (trayIntaking.changedToPressed()) {
            tray.moveToPreset(1);
        } else if (trayStacking.changedToPressed()) {
            tray.moveToPreset(2);
        }

        // TWO BAR

        if (twoBarDown.isPressed()) {
            twoBar.moveVelocity(-200);
        } else if (twoBarUp.isPressed()) {
            twoBar.moveVelocity(200);
        } else {
            twoBar.runNormally();
        }

        if (twoBarIntaking.changedToPressed()) {
            twoBar.moveToPreset(1);
        } else if (twoBarLowTower.changedToPressed()) {
            twoBar.moveToPreset(2);
        } else if (twoBarMidTower.changedToPressed()) {
            twoBar.moveToPreset(3);
        }

        pros::delay(20);
	}
}
