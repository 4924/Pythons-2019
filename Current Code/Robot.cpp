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
#include <Controller.h>


/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::IterativeRobot {

	//drivetrain setup
	frc::Spark m_frontLeft{2};
	frc::Spark m_rearLeft{3};
	frc::SpeedControllerGroup m_left{m_frontLeft, m_rearLeft};

	frc::Spark m_frontRight{0};
	frc::Spark m_rearRight{1};
	frc::SpeedControllerGroup m_right{m_frontRight, m_rearRight};

	frc::DifferentialDrive m_drive{m_left, m_right};

	frc::Spark m_armMotors{4};
	frc::Spark m_intakeMotor{5};
	//drivetrain setup

	//setup joysticks
	//Joystick::Joystick(0);

	frc::Joystick m_stick{1};
	Joystick m_Xbox{0};
	//setup joysticks

	//Random variables
	int tankDrive = -1;
	bool toggled;
	bool toggled2;
	float speed;
	float armSpeed;
	float intakeSpeed;
	//Random variables

private:

	void RobotInit()
	{
		CameraServer::GetInstance()->StartAutomaticCapture(0);
		CameraServer::GetInstance()->StartAutomaticCapture(1);
	}


public:


	void TeleopInit() {

	}

	void TeleopPeriodic() {

		if (m_Xbox.GetRawAxis(1) > 0.55 and speed < 0.3) {
			speed += 0.05;
		} if (m_Xbox.GetRawAxis(1) < 0.45 and speed < 0.3) {
			speed += 0.05;
		} else {
			speed -= 0.05;
		}

		//speed set

		if (speed > 1) {
			speed = 1;
		}

		else if (speed < 0) {
			speed = 0;
		}

		armSpeed = -0.25;
		intakeSpeed = 0;
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
			m_drive.ArcadeDrive(-m_Xbox.GetRawAxis(1) * (speed - 0.5), m_Xbox.GetRawAxis(0) * (speed - 0.5));
		} else if (tankDrive==1){
			m_drive.TankDrive(m_Xbox.GetRawAxis(0) * speed, -m_Xbox.GetRawAxis(1), m_Xbox.GetRawButton(6));
		}
		//drive!

		m_armMotors.Set(m_Xbox.GetRawAxis(5) * armSpeed);

		if (m_Xbox.GetRawButtonPressed(5)) {
			m_intakeMotor.Set(intakeSpeed + .75);
		} else if (m_Xbox.GetRawButtonReleased(5)) {
			m_intakeMotor.Set(intakeSpeed);
		}

		if (m_Xbox.GetRawButtonPressed(6)) {
			m_intakeMotor.Set(intakeSpeed -0.75);
		} else if (m_Xbox.GetRawButtonReleased(6)) {
			m_intakeMotor.Set(intakeSpeed);
		}
	}


};

START_ROBOT_CLASS(Robot)
