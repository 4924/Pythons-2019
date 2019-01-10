/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Drive/MecanumDrive.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <Spark.h>
#include <wpilib.h>
/**
 * This is a demo program showing how to use Mecanum control with the
 * MecanumDrive class.
 */
class Robot : public frc::IterativeRobot {
private:
	static constexpr int kFrontLeftChannel = 0;
	static constexpr int kRearLeftChannel = 1;
	static constexpr int kFrontRightChannel = 4;
	static constexpr int kRearRightChannel = 5;

	static constexpr int kJoystickChannel = 0;

	frc::Spark m_frontLeft{kFrontLeftChannel};
	frc::Spark m_rearLeft{kRearLeftChannel};
	frc::Spark m_frontRight{kFrontRightChannel};
	frc::Spark m_rearRight{kRearRightChannel};

	frc::MecanumDrive m_mechanumDrive{m_frontLeft, m_rearLeft, m_frontRight, m_rearRight};

	frc::Joystick m_Xbox{kJoystickChannel};

	frc::AnalogGyro Gyro{1};

public:
	void RobotInit() {
		// Invert the left side motors
		// You may need to change or remove this to match your robot
		m_frontLeft.SetInverted(true);
		m_rearLeft.SetInverted(false);
	}

	void TeleopInit() {
		Gyro.Reset();
	}

	void TeleopPeriodic() override {
		/* Use the joystick X axis for lateral movement, Y axis for
		 * forward
		 * movement, and Z axis for rotation.
		 */
		m_mechanumDrive.DriveCartesian(m_Xbox.GetRawAxis(0), m_Xbox.GetRawAxis(1), m_Xbox.GetRawAxis(4));
	}


};

START_ROBOT_CLASS(Robot)
