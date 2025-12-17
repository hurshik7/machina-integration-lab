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
		return static_cast<unsigned int>((200.0 * exp((800.0 - GetPassengersWeight()) / 500.0)) + 0.5);
	}

	unsigned int Airplane::GetDriveSpeed() const
	{
		return static_cast<unsigned int>(4.0 * exp(((400.0 - GetPassengersWeight()) / 70.0)) + 0.5);
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