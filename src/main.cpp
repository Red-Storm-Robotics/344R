#include "main.h"
#include "ports.h"
#include "lift.h"
#include "intake.h"
#include "tray.h"
#include "twobar.h"

Controller controller;

auto chassis = ChassisControllerBuilder()
                .withMotors(M_DRIVE_FL, M_DRIVE_FR, M_DRIVE_RR, M_DRIVE_RL)
                .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
                .build();

Intake intake;

Tray tray;

// TWO BAR
TwoBar twoBar;

// AUTONOMOUS SELECTION
bool redAlliance = true;
bool protectedSide = true;
bool autonomousEnabled = true;

void toggleAlliance() {
    redAlliance = !redAlliance;
    pros::lcd::set_text(3, redAlliance ? "Red Alliance" : "Blue Alliance");
}
void toggleSide() {
    protectedSide = !protectedSide;
    pros::lcd::set_text(4, protectedSide ? "Protected Side" : "Unprotected Side");
}
void toggleEnabled() {
    autonomousEnabled = !autonomousEnabled;
    pros::lcd::set_text(5, autonomousEnabled ? "Autonomous Enabled" : "Autonomous Disabled");
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::delay(10);
	pros::lcd::initialize();
    pros::lcd::set_text(0, "344R code, built on:");
	pros::lcd::set_text(1, __DATE__);
    pros::lcd::set_text(2, __TIME__);

    pros::lcd::set_text(3, redAlliance ? "Red Alliance" : "Blue Alliance");
    pros::lcd::set_text(4, protectedSide ? "Protected Side" : "Unprotected Side");
    pros::lcd::set_text(5, autonomousEnabled ? "Autonomous Enabled" : "Autonomous Disabled");

    // // FIXME: tune
    // twoBar.presets[0] = 0; // Stowed
    // twoBar.presets[1] = 90; // Intaking
    // twoBar.presets[2] = 180; // Low Tower
    // twoBar.presets[3] = 360; // Mid Tower

    pros::lcd::register_btn0_cb(toggleAlliance);
    pros::lcd::register_btn1_cb(toggleSide);
    pros::lcd::register_btn2_cb(toggleEnabled);
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
    if (!autonomousEnabled) return;

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
        double speed = controller.getAnalog(ControllerAnalog::leftY);
        double steer = controller.getAnalog(ControllerAnalog::rightX);

        chassis->getModel()->arcade(speed, steer);

        intake.opcontrol();

        // TRAY

        tray.opcontrol();

        // TWO BAR

        twoBar.opcontrol();

        pros::delay(20);
	}
}
