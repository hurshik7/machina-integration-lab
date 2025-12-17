#pragma once
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Vehicles/Interfaces/IFlyable.h"
#include "../../Engine/Vehicles/Interfaces/ISailable.h"

namespace game {
namespace vehicles {

class Boatplane : public engine::vehicles::Vehicle, public engine::vehicles::interfaces::IFlyable, public engine::vehicles::interfaces::ISailable
{
public:
	Boatplane(unsigned int maxPassengersCount);
	virtual ~Boatplane();

	// Move-only (inherited from Vehicle)
	Boatplane(Boatplane&&) = default;
	Boatplane& operator=(Boatplane&&) = default;

	virtual unsigned int GetFlySpeed() const;
	virtual unsigned int GetSailSpeed() const;
	virtual unsigned int GetMaxSpeed() const;
	virtual void TravelByMachina(const engine::core::TravelContext& context) override;

private:
	enum { IDLE_TIME = 3, MOVE_TIME = 1};
};

} // namespace vehicles
} // namespace game