#include <cmath>
#include <algorithm>
#include "UBoat.h"

namespace game {
namespace vehicles {

UBoat::UBoat()
	: Vehicle(50)
	, mSailing(550)   // base sail speed parameter
	, mDiving(150)    // base dive speed parameter
{
}

UBoat::~UBoat()
{
}

unsigned int UBoat::GetMaxSpeed() const
{
	return GetSailSpeed() > GetDiveSpeed() ? GetSailSpeed() : GetDiveSpeed();
}

unsigned int UBoat::GetSailSpeed() const
{
	double baseParam = static_cast<double>(mSailing.GetSailSpeed());
	return static_cast<unsigned int>(std::max(static_cast<int>((baseParam - GetPassengersWeight() / 10.0) + 0.5), 200));
}

unsigned int UBoat::GetDiveSpeed() const
{
	double baseParam = static_cast<double>(mDiving.GetDiveSpeed());
	return static_cast<unsigned int>((500 * log((GetPassengersWeight() + baseParam) / baseParam) + 30) + 0.5);
}

const engine::capabilities::SailingCapability& UBoat::GetSailingCapability() const
{
	return mSailing;
}

const engine::capabilities::DivingCapability& UBoat::GetDivingCapability() const
{
	return mDiving;
}

void UBoat::TravelByMachina(const engine::core::TravelContext& /*context*/)
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
