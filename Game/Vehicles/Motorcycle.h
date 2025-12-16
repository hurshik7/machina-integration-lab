#pragma once
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Vehicles/Interfaces/IDrivable.h"

namespace game {
namespace vehicles {

class Motorcycle : public engine::vehicles::Vehicle, public engine::vehicles::interfaces::IDrivable
{
public:
	Motorcycle();
	virtual ~Motorcycle();

	virtual unsigned int GetMaxSpeed() const;
	virtual unsigned int GetDriveSpeed() const;
	virtual void TravelByMachina(const engine::core::TravelContext& context) override;

private:
	enum { IDLE_TIME = 1, MOVE_TIME = 5};
};

} // namespace vehicles
} // namespace game