#include <cmath>
#include <memory>
#include <vector>
#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"
#include "../../Engine/Interfaces/IPassenger.h"

namespace game {
namespace vehicles {

using engine::interfaces::IPassenger;

Airplane::Airplane(unsigned int maxPassengersCount)
	: Vehicle(maxPassengersCount)
	, mFlying(800)    // base fly speed parameter
	, mDriving(400)   // base drive speed parameter
{
}

Airplane::~Airplane()
{
}

Boatplane Airplane::operator+(Boat& boat)
{
	unsigned int totalMaxPassengersCount = GetMaxPassengersCount() + boat.GetMaxPassengersCount();
	Boatplane bp(totalMaxPassengersCount);

	std::vector<std::unique_ptr<const IPassenger>> myPassengers = ReleaseAllPassengers();
	for (std::unique_ptr<const IPassenger>& passenger : myPassengers)
	{
		bp.AddPassenger(std::move(passenger));
	}

	std::vector<std::unique_ptr<const IPassenger>> boatPassengers = boat.ReleaseAllPassengers();
	for (std::unique_ptr<const IPassenger>& passenger : boatPassengers)
	{
		bp.AddPassenger(std::move(passenger));
	}

	return bp;
}

unsigned int Airplane::GetMaxSpeed() const
{
	unsigned int flyingSpeed = GetFlySpeed();
	unsigned int drivingSpeed = GetDriveSpeed();
	return flyingSpeed > drivingSpeed ? flyingSpeed : drivingSpeed;
}

unsigned int Airplane::GetFlySpeed() const
{
	unsigned int baseParam = mFlying.GetFlySpeed();
	return static_cast<unsigned int>((200.0 * exp((static_cast<double>(baseParam) - GetPassengersWeight()) / 500.0)) + 0.5);
}

unsigned int Airplane::GetDriveSpeed() const
{
	unsigned int baseParam = mDriving.GetDriveSpeed();
	return static_cast<unsigned int>(4.0 * exp((static_cast<double>(baseParam) - GetPassengersWeight()) / 70.0) + 0.5);
}

const engine::capabilities::FlyingCapability& Airplane::GetFlyingCapability() const
{
	return mFlying;
}

const engine::capabilities::DrivingCapability& Airplane::GetDrivingCapability() const
{
	return mDriving;
}

void Airplane::TravelByMachina(const engine::core::TravelContext& /*context*/)
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
