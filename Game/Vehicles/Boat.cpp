#include <memory>
#include <vector>
#include "Boat.h"
#include "Airplane.h"
#include "Boatplane.h"
#include "Person.h"

namespace game {
namespace vehicles {

	Boat::Boat(unsigned int maxPassengersCount)
		: Vehicle(maxPassengersCount)
	{
	}

	Boat::~Boat()
	{
	}

	Boatplane Boat::operator+(Airplane& plane)
	{
		unsigned int totalMaxPassengersCount = GetMaxPassengersCount() + plane.GetMaxPassengersCount();
		Boatplane bp(totalMaxPassengersCount);

		std::vector<std::unique_ptr<const Person>> planePassengers = plane.ReleaseAllPassengers();
		for (std::unique_ptr<const Person>& passenger : planePassengers)
		{
			bp.AddPassenger(std::move(passenger));
		}

		std::vector<std::unique_ptr<const Person>> myPassengers = ReleaseAllPassengers();
		for (std::unique_ptr<const Person>& passenger : myPassengers)
		{
			bp.AddPassenger(std::move(passenger));
		}

		return bp;
	}

	unsigned int Boat::GetSailSpeed() const
	{
		return std::max(static_cast<int>(800 - 10 * GetPassengersWeight()), 20);
	}

	unsigned int Boat::GetMaxSpeed() const
	{
		return GetSailSpeed();
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