#pragma once
#include <memory>
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Capabilities/DrivingCapability.h"

namespace game {
namespace vehicles {

class Trailer;

class Sedan : public engine::vehicles::Vehicle
{
public:
	Sedan();
	virtual ~Sedan();

	// Move-only
	Sedan(const Sedan&) = delete;
	Sedan& operator=(const Sedan&) = delete;
	Sedan(Sedan&& other) noexcept;
	Sedan& operator=(Sedan&& rhs) noexcept;

	bool AddTrailer(std::unique_ptr<Trailer> trailer);
	bool RemoveTrailer();
	const Trailer* GetTrailer() const;

	virtual unsigned int GetMaxSpeed() const override;
	virtual void TravelByMachina(const engine::core::TravelContext& context) override;

	// Capability accessor
	unsigned int GetDriveSpeed() const;
	const engine::capabilities::DrivingCapability& GetDrivingCapability() const;

private:
	enum { IDLE_TIME = 1, MOVE_TIME = 5, IDLE_TIME_TRAIL_ON = 2 };

	engine::capabilities::DrivingCapability mDriving;
	std::unique_ptr<Trailer> mTrailer;
};

} // namespace vehicles
} // namespace game
