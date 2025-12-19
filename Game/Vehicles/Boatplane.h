#pragma once
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Interfaces/IFlyable.h"
#include "../../Engine/Interfaces/ISailable.h"

namespace game {
namespace vehicles {

class Boatplane : public engine::vehicles::Vehicle, public engine::interfaces::IFlyable, public engine::interfaces::ISailable
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