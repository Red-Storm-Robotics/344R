#pragma once

// PORT MAPPINGS
#define M_DRIVE_FL 1
#define M_DRIVE_FR -2
#define M_DRIVE_RL 9
#define M_DRIVE_RR -10

#define M_INTAKE_L 3
#define M_INTAKE_R -8

#define M_TRAY 5
#define M_TWOBAR 6

// CONTROL MAPPINGS
// Drivetrain
#define C_ARCADE_SPEED ControllerAnalog::leftY
#define C_ARCADE_STEER ControllerAnalog::rightX

#define C_TANK_LEFT  ControllerAnalog::leftY
#define C_TANK_RIGHT ControllerAnalog::rightY

// Intake
#define C_INTAKE_FWD ControllerDigital::R1
#define C_INTAKE_REV ControllerDigital::R2

// Tray
#define C_TRAY_UP   ControllerDigital::up
#define C_TRAY_DOWN ControllerDigital::down

// Two Bar

#define C_TWOBAR_UP   ControllerDigital::L1
#define C_TWOBAR_DOWN ControllerDigital::L2

// Combined Presets

#define C_PRESET_INTAKE ControllerDigital::B
#define C_PRESET_STACK ControllerDigital::A

// PRESET SETTINGS
#define P_TRAY_INTAKE 20
#define P_TRAY_STACK  540

// TODO: Find actual values for this
#define P_TWOBAR_STACK 0
#define P_TWOBAR_INTAKE 120
