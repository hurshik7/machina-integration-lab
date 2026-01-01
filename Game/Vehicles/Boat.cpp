#include <memory>
#include <vector>
#include <algorithm>
#include "Boat.h"
#include "Airplane.h"
#include "Boatplane.h"
#include "../../Engine/Interfaces/IPassenger.h"

namespace game {
namespace vehicles {

using engine::interfaces::IPassenger;

Boat::Boat(unsigned int maxPassengersCount)
	: Vehicle(maxPassengersCount)
	, mSailing(800)  // base sail speed parameter
{
}

Boat::~Boat()
{
}

Boatplane Boat::operator+(Airplane& plane)
{
	unsigned int totalMaxPassengersCount = GetMaxPassengersCount() + plane.GetMaxPassengersCount();
	Boatplane bp(totalMaxPassengersCount);

	std::vector<std::unique_ptr<const IPassenger>> planePassengers = plane.ReleaseAllPassengers();
	for (std::unique_ptr<const IPassenger>& passenger : planePassengers)
	{
		bp.AddPassenger(std::move(passenger));
	}

	std::vector<std::unique_ptr<const IPassenger>> myPassengers = ReleaseAllPassengers();
	for (std::unique_ptr<const IPassenger>& passenger : myPassengers)
	{
		bp.AddPassenger(std::move(passenger));
	}

	return bp;
}

unsigned int Boat::GetSailSpeed() const
{
	int baseSpeed = static_cast<int>(mSailing.GetSailSpeed());
	return static_cast<unsigned int>(std::max(baseSpeed - 10 * static_cast<int>(GetPassengersWeight()), 20));
}

unsigned int Boat::GetMaxSpeed() const
{
	return GetSailSpeed();
}

const engine::capabilities::SailingCapability& Boat::GetSailingCapability() const
{
	return mSailing;
}

void Boat::TravelByMachina(const engine::core::TravelContext& /*context*/)
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
