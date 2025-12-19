#pragma once

#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Interfaces/IFlyable.h"
#include "../../Engine/Interfaces/IDrivable.h"

namespace game {
namespace vehicles {

class Boat;
class Boatplane;

class Airplane : public engine::vehicles::Vehicle, public engine::interfaces::IFlyable, public engine::interfaces::IDrivable
{
public:
	Airplane(unsigned int maxPassengersCount);
	virtual ~Airplane();

	Boatplane operator+(Boat& boat);

	virtual unsigned int GetMaxSpeed() const;
	virtual unsigned int GetFlySpeed() const;
	virtual unsigned int GetDriveSpeed() const;
	virtual void TravelByMachina(const engine::core::TravelContext& context) override;

private:
	enum { IDLE_TIME = 3, MOVE_TIME = 1 };
};

} // namespace vehicles
} // namespace game