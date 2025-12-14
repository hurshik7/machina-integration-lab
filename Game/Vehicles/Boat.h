#pragma once
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Vehicles/Interfaces/ISailable.h"

namespace game {
namespace vehicles {

class Airplane;
class Boatplane;

class Boat : public engine::vehicles::Vehicle, public engine::vehicles::interfaces::ISailable
{
public:
	Boat(unsigned int maxPassengersCount);
	virtual ~Boat();

	Boatplane operator+(Airplane& plane);
	virtual unsigned int GetSailSpeed() const;
	virtual unsigned int GetMaxSpeed() const;
	virtual void TravelByMachina();

private:
	enum { IDLE_TIME = 1, MOVE_TIME = 2 };
};

} // namespace vehicles
} // namespace game