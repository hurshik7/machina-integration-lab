#pragma once
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Capabilities/FlyingCapability.h"
#include "../../Engine/Capabilities/SailingCapability.h"

namespace game {
namespace vehicles {

class Boatplane : public engine::vehicles::Vehicle
{
public:
	Boatplane(unsigned int maxPassengersCount);
	virtual ~Boatplane();

	// Move-only (inherited from Vehicle)
	Boatplane(Boatplane&&) = default;
	Boatplane& operator=(Boatplane&&) = default;

	virtual unsigned int GetMaxSpeed() const override;
	virtual void TravelByMachina(const engine::core::TravelContext& context) override;

	// Capability accessors
	unsigned int GetFlySpeed() const;
	unsigned int GetSailSpeed() const;

	const engine::capabilities::FlyingCapability& GetFlyingCapability() const;
	const engine::capabilities::SailingCapability& GetSailingCapability() const;

private:
	enum { IDLE_TIME = 3, MOVE_TIME = 1 };

	engine::capabilities::FlyingCapability mFlying;
	engine::capabilities::SailingCapability mSailing;
};

} // namespace vehicles
} // namespace game
