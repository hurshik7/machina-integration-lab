#pragma once
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Vehicles/Interfaces/ISailable.h"
#include "../../Engine/Vehicles/Interfaces/IDivable.h"

namespace game {
namespace vehicles {

class UBoat : public engine::vehicles::Vehicle, public engine::vehicles::interfaces::ISailable, public engine::vehicles::interfaces::IDivable
{
public:
	UBoat();
	virtual ~UBoat();

	virtual unsigned int GetMaxSpeed() const;
	virtual unsigned int GetSailSpeed() const;
	virtual unsigned int GetDiveSpeed() const;
	virtual void TravelByMachina();

private:
	enum { IDLE_TIME = 4, MOVE_TIME = 2 };
};

} // namespace vehicles
} // namespace game