/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/drive/DifferentialDrive.h>
#include <frc/IterativeRobot.h>
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <frc/WPILib.h>
#include <frc/Controller.h>
#include <cameraserver/CameraServer.h>
#include <cstdlib>
#include <iostream>


/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::IterativeRobot{

	//drivetrain setup
	frc::Spark m_frontLeft{0};
	frc::Spark m_rearLeft{1};
	frc::SpeedControllerGroup m_left{m_frontLeft, m_rearLeft};

	frc::Spark m_frontRight{2};
	frc::Spark m_rearRight{3};
	frc::SpeedControllerGroup m_right{m_frontRight, m_rearRight};

	frc::DifferentialDrive m_drive{m_left, m_right};

	frc::Spark m_leftArmMotor{4};
	frc::Spark m_rightArmMotor{5};
	frc::Spark m_intakeMotor{6};

	frc::Joystick m_Xbox{0};

	//frc::StartRobot<Robot>();

	//drivetrain setup

	//setup joysticks

/*Joystick m_Xboxjoystick

public:
     Robot(){
     }
     void RobotInit() {
       m_Xboxjoystick = new Joystick(1);
     }
*/

	//Joystick(m_Xbox){0}
	//frc::Joystick m_stick{1};

	//setup joysticks

	//Random variables
	int tankDrive = -1;
	bool toggled;
	bool toggled2;
	float accelstr;
	float acceltrn;
	float maxstr;
	float maxtrn;
	float speed; // straight
	float speedF;
	float speedB;
	float speedtrn;
	float turning;
	float turns;
	float turningL;
	float turningR;
	float armSpeed;
	float intakeSpeed;
	float turningspeedL;
	float turningspeedR;
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
		//speed set
		speed = 0;
		speedtrn = 0.01;

		accelstr = 0.01;  //.05 last time
		maxstr = abs(m_Xbox.GetRawAxis(1));

		if (m_Xbox.GetRawAxis(1) > 0.1) {
			speed = -m_Xbox.GetRawAxis(1) + accelstr; 
		} else if (m_Xbox.GetRawAxis(1) < -0.1) {
			speed = -m_Xbox.GetRawAxis(1) - accelstr;
		} else{
			speed = 0;
		}
		//else if (m_Xbox.GetRawAxis(1) > 0.1 and m_Xbox.GetRawAxis(1) < -0.05) {
			//if (speed > 0) {
				//speed = speedF - accel;
			//} else if (speed < 0) {
				//speed = speedF + accel;
			//}
		//}

		if (m_Xbox.GetRawAxis(0) > 0.01) {
			turningR = m_Xbox.GetRawAxis(0) + speedtrn;
		} else if (m_Xbox.GetRawAxis(0) < -0.01) {
			turningL = -m_Xbox.GetRawAxis(0) + speedtrn;
		} else{
			turns = 0;
			turningR = 0;
			turningL = 0;
		}

		if (m_Xbox.GetRawAxis(3) > 0.01) {
			turns = turns * 2;
		} else if (m_Xbox.GetRawAxis(3) < 0.01) {
			turns = turns * 1;
		} else if (m_Xbox.GetRawAxis(2) > 0.01) {
			turns = turns * 0.5;
		} else if (m_Xbox.GetRawAxis(2) < -0.01) {
			turns = turns * 1;
		}
		
		/*if (speed > maxstr) {
			speed = maxstr;
		} else if (speed < -maxstr) {
			speed = -maxstr;
		}*/
		/*if (m_Xbox.GetRawAxis(2) > -0.1) {
			turningR = m_Xbox.GetRawAxis(2) * speed;
		}

		// else if (m_Xbox.GetRawAxis(2) < 0.1) {
			//turningR = m_Xbox.GetRawAxis(2) * -speed;
		//} 
			if (m_Xbox.GetRawAxis(3) > -0.1) {	
				turningL = m_Xbox.GetRawAxis(3) * speed;
				}

			//	 else if (m_Xbox.GetRawAxis(3) < 0.1) {
		//	turningL = m_Xbox.GetRawAxis(3) * -speed;
	//	}
		*/
	if (turningR > turningL) {
		turns = turningR;
	} else if (turningL > turningR) {
		turns = -turningL;
	}

/*
acceltrn = 0.02;  //.05 last time
		maxtrn = abs(m_Xbox.GetRawAxis(0));

if (m_Xbox.GetRawAxis(0) > -0.1) {
			turning = turningspeedL + acceltrn;
		} else if (m_Xbox.GetRawAxis(1) < -0.1) {
			turning = turningspeedR - acceltrn;
	

		if (turning > maxtrn) {
			turning = maxtrn;
		} else if (turning < -maxtrn) {
			turning = -maxtrn;
		}
*/

		armSpeed = -0.6 ;
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
			m_drive.ArcadeDrive(speed, turns);
		} else if (tankDrive==1){
			m_drive.TankDrive(m_Xbox.GetRawAxis(0) * speed, m_Xbox.GetRawAxis(1), m_Xbox.GetRawButton(6));
		}
		//drive!

		m_leftArmMotor.Set(m_Xbox.GetRawAxis(5) * armSpeed);
		m_rightArmMotor.Set(m_Xbox.GetRawAxis(5) * armSpeed);

		if (m_Xbox.GetRawButtonPressed(5)) {
			m_intakeMotor.Set(intakeSpeed + 0.25);
		} else if (m_Xbox.GetRawButtonReleased(5)) {
			m_intakeMotor.Set(intakeSpeed);
		}

		if (m_Xbox.GetRawButtonPressed(6)) {
			m_intakeMotor.Set(intakeSpeed -0.7);
		} else if (m_Xbox.GetRawButtonReleased(6)) {
			m_intakeMotor.Set(intakeSpeed);
		}
	}
int main()
{
	return 0;
};
};
START_ROBOT_CLASS(Robot)
