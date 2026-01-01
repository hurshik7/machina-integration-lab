#pragma once
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Capabilities/SailingCapability.h"
#include "../../Engine/Capabilities/DivingCapability.h"

namespace game {
namespace vehicles {

class UBoat : public engine::vehicles::Vehicle
{
public:
	UBoat();
	virtual ~UBoat();

	// Move-only (inherited from Vehicle)
	UBoat(UBoat&&) = default;
	UBoat& operator=(UBoat&&) = default;

	virtual unsigned int GetMaxSpeed() const override;
	virtual void TravelByMachina(const engine::core::TravelContext& context) override;

	// Capability accessors
	unsigned int GetSailSpeed() const;
	unsigned int GetDiveSpeed() const;

	const engine::capabilities::SailingCapability& GetSailingCapability() const;
	const engine::capabilities::DivingCapability& GetDivingCapability() const;

private:
	enum { IDLE_TIME = 4, MOVE_TIME = 2 };

	engine::capabilities::SailingCapability mSailing;
	engine::capabilities::DivingCapability mDiving;
};

} // namespace vehicles
} // namespace game
