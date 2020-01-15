#pragma once

// PORT MAPPINGS
#define M_DRIVE_FL 1
#define M_DRIVE_FR -2
#define M_DRIVE_RL 9
#define M_DRIVE_RR -10

#define M_INTAKE_L -3
#define M_INTAKE_R 8

#define M_TRAY 5
#define M_TWOBAR 6

// CONTROL MAPPINGS
// Drivetrain
#define C_ARCADE_SPEED ControllerAnalog::leftY
#define C_ARCADE_STEER ControllerAnalog::rightX

#define C_TANK_LEFT  ControllerAnalog::leftY
#define C_TANK_RIGHT ControllerAnalog::rightY

// Intake
#define C_INTAKE_FWD ControllerDigital::L1
#define C_INTAKE_REV ControllerDigital::L2

// Tray
#define C_TRAY_STOWED ControllerDigital::left
#define C_TRAY_STACK  ControllerDigital::R1
#define C_TRAY_INTAKE ControllerDigital::R2

#define C_TRAY_UP   ControllerDigital::X
#define C_TRAY_DOWN ControllerDigital::Y

// Two Bar
//#define C_TWOBAR_STOWED
#define C_TWOBAR_INTAKE ControllerDigital::down
#define C_TWOBAR_LOW_TOWER ControllerDigital::B
#define C_TWOBAR_MID_TOWER ControllerDigital::A

#define C_TWOBAR_UP   ControllerDigital::up
#define C_TWOBAR_DOWN ControllerDigital::right

// PRESET SETTINGS
#define P_TRAY_STOWED 0
#define P_TRAY_INTAKE 100
#define P_TRAY_STACK  540

// TODO: Find actual values for this
#define P_TWOBAR_STOWED 0
#define P_TWOBAR_INTAKE 90
#define P_TWOBAR_LOW_TOWER 180
#define P_TWOBAR_MID_TOWER 270
