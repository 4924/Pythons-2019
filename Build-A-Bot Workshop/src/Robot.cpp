/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Drive/DifferentialDrive.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <Spark.h>
#include <wpilib.h>
#include <XboxController.h>
#include <DoubleSolenoid.h>

/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::IterativeRobot {

	//drivetrain setup
	frc::Spark m_frontLeft{0};
	frc::Spark m_rearLeft{0};
	frc::SpeedControllerGroup m_left{m_frontLeft, m_rearLeft};

	frc::Spark m_frontRight{1};
	frc::Spark m_rearRight{1};
	frc::SpeedControllerGroup m_right{m_frontRight, m_rearRight};

	frc::DifferentialDrive m_drive{m_left, m_right};
	//drivetrain setup

	//pnuematics
	frc::Compressor Compressor1 {0};
	frc::DoubleSolenoid L_Solenoid {0,1};
	frc::DoubleSolenoid R_Solenoid {2,3};
	//pnuematics

	//setup joysticks
	//frc::Joystick m_stick{1};
	Joystick m_Xbox{0};
	//setup joysticks

	//Random variables
	int tankDrive = -1;
	bool toggled;
	bool toggled2;
	float speed;
	//Random variables

public:

	void DisabledPeriodic() {
		if (m_Xbox.GetRawButton(8)){

		}
	}

	void TeleopInit() {
		Compressor1.SetClosedLoopControl(true);
		CameraServer::GetInstance()->StartAutomaticCapture();

	}

	void TeleopPeriodic() {

		//pnuematics shenanigans
		if (m_Xbox.GetRawButtonPressed(2) and toggled2 == false) {
			toggled2 = true;
			R_Solenoid.Set(frc::DoubleSolenoid::Value::kReverse);
			L_Solenoid.Set(frc::DoubleSolenoid::Value::kReverse);
		} else if (m_Xbox.GetRawButtonReleased(2)) {
			toggled2 = false;
			R_Solenoid.Set(frc::DoubleSolenoid::Value::kForward);
			L_Solenoid.Set(frc::DoubleSolenoid::Value::kForward);
		}
		//pnuematics shenanigans

		//speed set
		speed = m_Xbox.GetRawAxis(3) + 0.5;
		if (speed > 1){
			speed = 1;
		} else if (speed < -1) {
			speed = -1;
		}
		//speed set

		//tank/arcade toggling
		if (m_Xbox.GetRawButtonPressed(1) and toggled == false) {
			tankDrive *= -1;
			toggled = true;
		} else if (m_Xbox.GetRawButtonReleased(1)) {
			toggled = false;
		}
		//tank/arcade toggling

		//drive!
		if (tankDrive==-1) {
			m_drive.ArcadeDrive(-m_Xbox.GetRawAxis(1) * speed, m_Xbox.GetRawAxis(0) * speed);
		} else if (tankDrive==1){
			m_drive.CurvatureDrive(-m_Xbox.GetRawAxis(1) * speed, m_Xbox.GetRawAxis(4) + 0.15, m_Xbox.GetRawButton(6));
		}
		//drive!
	}


};

START_ROBOT_CLASS(Robot)
