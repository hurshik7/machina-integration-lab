#pragma once
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Capabilities/DrivingCapability.h"

namespace game {
namespace vehicles {

class Motorcycle : public engine::vehicles::Vehicle
{
public:
	Motorcycle();
	virtual ~Motorcycle();

	// Move-only (inherited from Vehicle)
	Motorcycle(Motorcycle&&) = default;
	Motorcycle& operator=(Motorcycle&&) = default;

	virtual unsigned int GetMaxSpeed() const override;
	virtual void TravelByMachina(const engine::core::TravelContext& context) override;

	// Capability accessor
	unsigned int GetDriveSpeed() const;
	const engine::capabilities::DrivingCapability& GetDrivingCapability() const;

private:
	enum { IDLE_TIME = 1, MOVE_TIME = 5 };

	engine::capabilities::DrivingCapability mDriving;
};

} // namespace vehicles
} // namespace game
