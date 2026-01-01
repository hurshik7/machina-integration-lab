#include <cmath>
#include <algorithm>
#include "Motorcycle.h"

namespace game {
namespace vehicles {

Motorcycle::Motorcycle()
	: Vehicle(2)
	, mDriving(400)   // base drive speed parameter
{
}

Motorcycle::~Motorcycle()
{
}

unsigned int Motorcycle::GetMaxSpeed() const
{
	return GetDriveSpeed();
}

unsigned int Motorcycle::GetDriveSpeed() const
{
	double baseSpeed = static_cast<double>(mDriving.GetDriveSpeed());
	double weight = static_cast<double>(GetPassengersWeight());
	return static_cast<unsigned int>(std::max(baseSpeed + (2 * weight) - pow(weight / 15.0, 3) + 0.5, 0.0));
}

const engine::capabilities::DrivingCapability& Motorcycle::GetDrivingCapability() const
{
	return mDriving;
}

void Motorcycle::TravelByMachina(const engine::core::TravelContext& /*context*/)
{
	unsigned int moveTime = GetMoveTime();
	unsigned int idleTime = GetIdleTime();
	unsigned int speed = GetMaxSpeed();
	//check available
	if (moveTime < MOVE_TIME)
	{
		//move
		AddMoveTime();
		AddOdo(speed);
	}
	else if (moveTime == MOVE_TIME && idleTime < IDLE_TIME)
	{
		AddIdleTime();
		if (GetIdleTime() == IDLE_TIME)
		{
			ResetMoveTime();
			ResetIdleTIme();
		}
	}
}

} // namespace vehicles
} // namespace game
