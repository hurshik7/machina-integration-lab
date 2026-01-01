#pragma once
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Capabilities/SailingCapability.h"

namespace game {
namespace vehicles {

class Airplane;
class Boatplane;

class Boat : public engine::vehicles::Vehicle
{
public:
	Boat(unsigned int maxPassengersCount);
	virtual ~Boat();

	// Move-only (inherited from Vehicle)
	Boat(Boat&&) = default;
	Boat& operator=(Boat&&) = default;

	Boatplane operator+(Airplane& plane);

	virtual unsigned int GetMaxSpeed() const override;
	virtual void TravelByMachina(const engine::core::TravelContext& context) override;

	// Capability accessor
	unsigned int GetSailSpeed() const;
	const engine::capabilities::SailingCapability& GetSailingCapability() const;

private:
	enum { IDLE_TIME = 1, MOVE_TIME = 2 };

	engine::capabilities::SailingCapability mSailing;
};

} // namespace vehicles
} // namespace game
