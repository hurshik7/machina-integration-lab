#include <cmath>
#include <algorithm>
#include "Boatplane.h"

namespace game {
namespace vehicles {

Boatplane::Boatplane(unsigned int maxPassengersCount)
	: Vehicle(maxPassengersCount)
	, mFlying(500)    // base fly speed parameter
	, mSailing(800)   // base sail speed parameter
{
}

Boatplane::~Boatplane()
{
}

unsigned int Boatplane::GetFlySpeed() const
{
	double baseParam = static_cast<double>(mFlying.GetFlySpeed());
	return static_cast<unsigned int>(round(150.0 * exp((baseParam - GetPassengersWeight()) / 300.0)));
}

unsigned int Boatplane::GetSailSpeed() const
{
	double baseParam = static_cast<double>(mSailing.GetSailSpeed());
	return static_cast<unsigned int>(std::max(static_cast<int>(round(baseParam - 1.7 * GetPassengersWeight())), 20));
}

unsigned int Boatplane::GetMaxSpeed() const
{
	unsigned int flyingSpeed = GetFlySpeed();
	unsigned int sailingSpeed = GetSailSpeed();
	return flyingSpeed > sailingSpeed ? flyingSpeed : sailingSpeed;
}

const engine::capabilities::FlyingCapability& Boatplane::GetFlyingCapability() const
{
	return mFlying;
}

const engine::capabilities::SailingCapability& Boatplane::GetSailingCapability() const
{
	return mSailing;
}

void Boatplane::TravelByMachina(const engine::core::TravelContext& /*context*/)
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
		//idle time
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
