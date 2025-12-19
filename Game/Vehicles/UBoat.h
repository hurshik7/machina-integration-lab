#pragma once
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Interfaces/ISailable.h"
#include "../../Engine/Interfaces/IDivable.h"

namespace game {
namespace vehicles {

class UBoat : public engine::vehicles::Vehicle, public engine::interfaces::ISailable, public engine::interfaces::IDivable
{
public:
	UBoat();
	virtual ~UBoat();

	virtual unsigned int GetMaxSpeed() const;
	virtual unsigned int GetSailSpeed() const;
	virtual unsigned int GetDiveSpeed() const;
	virtual void TravelByMachina(const engine::core::TravelContext& context) override;

private:
	enum { IDLE_TIME = 4, MOVE_TIME = 2 };
};

} // namespace vehicles
} // namespace game