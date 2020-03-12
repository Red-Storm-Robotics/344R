#include "main.h"
#include "ports.h"
#include "twoBarTray.h"
#include "intake.h"

Controller controller;

auto chassis = ChassisControllerBuilder()
                .withMotors(M_DRIVE_FL, M_DRIVE_FR, M_DRIVE_RR, M_DRIVE_RL)
                .withDimensions(AbstractMotor::gearset::green, {{4.1_in, 11.5_in}, imev5GreenTPR})
                .build();

auto profileController = AsyncMotionProfileControllerBuilder()
                            .withLimits({1.0, 1.0, 5.0})
                            .withOutput(chassis)
                            .buildMotionProfileController();

Intake intake;

TwoBarTray twoBarTray;

//ControllerButton autonBtn = ControllerButton(ControllerDigital::Y);

// AUTONOMOUS SELECTION
bool redAlliance = false;
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

    chassis->setTurnsMirrored(!redAlliance);

    twoBarTray.moveToPreset(P_MID_NUM);
    pros::Task::delay(500);
    twoBarTray.moveToPreset(P_INTK_NUM);
    pros::Task::delay(500);

    intake.switchToState(IntakeState::forward);

    // Drive forward, intake 4 cubes + preload
    profileController->generatePath({
      {0_in, 0_in, 0_deg},
      {40_in, 0_in, 0_deg}
    }, "A", {0.5, 1.0, 5.0});

    profileController->setTarget("A");
    profileController->waitUntilSettled();
    profileController->removePath("A");

    // Back up, prepare to intake 2 add'l cubes
    profileController->generatePath({
      {0_in, 24_in, 0_deg},
      {10_in, 24_in, 0_deg},
      {28_in, 0_in, 0_deg},
    }, "B");

    profileController->setTarget("B", true);
    profileController->waitUntilSettled();
    profileController->removePath("B");

    // Inatke 2 add'l cubes
    profileController->generatePath({
      {0_in, 0_in, 0_deg},
      {24_in, 0_in, 0_deg}
    }, "C", {0.5, 1.0, 5.0});

    profileController->setTarget("C");
    profileController->waitUntilSettled();
    profileController->removePath("C");

    intake.switchToState(IntakeState::stop);

    // Turn towards corner
    chassis->turnAngle(90_deg);
    chassis->waitUntilSettled();

    // Drive towards corner to stack cubes
    profileController->generatePath({
      {0_in, 0_in, 0_deg},
      {52_in, 28_in, 45_deg}
    }, "D");

    profileController->setTarget("D");
    profileController->waitUntilSettled();
    profileController->removePath("D");

    // Stack cubes
    twoBarTray.moveToPreset(P_STACK_NUM);
    pros::Task::delay(5000);

    intake.switchToState(IntakeState::reverse);
    pros::Task::delay(250);
    intake.switchToState(IntakeState::stop);

    profileController->generatePath({
      {0_in, 0_in, 0_deg},
      {16_in, 0_in, 0_deg}
    }, "E");

    profileController->setTarget("E", true);
    profileController->waitUntilSettled();
    profileController->removePath("E");
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
      //  if (autonBtn.changedToPressed()) {
      //      autonomous();
      //  }
        chassis->setMaxVelocity(200);

        double speed = controller.getAnalog(ControllerAnalog::leftY);
        double steer = controller.getAnalog(ControllerAnalog::rightX);

        chassis->getModel()->arcade(speed, steer);

        intake.opcontrol();

        // TRAY

        twoBarTray.opcontrol();

        pros::delay(20);
	}
}
