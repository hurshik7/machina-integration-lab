#pragma once

#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Capabilities/FlyingCapability.h"
#include "../../Engine/Capabilities/DrivingCapability.h"

namespace game {
namespace vehicles {

class Boat;
class Boatplane;

class Airplane : public engine::vehicles::Vehicle
{
public:
	Airplane(unsigned int maxPassengersCount);
	virtual ~Airplane();

	// Move-only (inherited from Vehicle)
	Airplane(Airplane&&) = default;
	Airplane& operator=(Airplane&&) = default;

	Boatplane operator+(Boat& boat);

	virtual unsigned int GetMaxSpeed() const override;
	virtual void TravelByMachina(const engine::core::TravelContext& context) override;

	// Capability accessors
	unsigned int GetFlySpeed() const;
	unsigned int GetDriveSpeed() const;

	const engine::capabilities::FlyingCapability& GetFlyingCapability() const;
	const engine::capabilities::DrivingCapability& GetDrivingCapability() const;

private:
	enum { IDLE_TIME = 3, MOVE_TIME = 1 };

	engine::capabilities::FlyingCapability mFlying;
	engine::capabilities::DrivingCapability mDriving;
};

} // namespace vehicles
} // namespace game
