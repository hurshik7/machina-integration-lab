#pragma once
#include <memory>
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Interfaces/IDrivable.h"

namespace game {
namespace vehicles {

class Trailer;

class Sedan : public engine::vehicles::Vehicle, public engine::interfaces::IDrivable
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
	virtual unsigned int GetMaxSpeed() const;
	virtual unsigned int GetDriveSpeed() const;
	virtual void TravelByMachina(const engine::core::TravelContext& context) override;

private:
	enum { IDLE_TIME = 1, MOVE_TIME = 5, IDLE_TIME_TRAIL_ON = 2 };
	std::unique_ptr<Trailer> mTrailer;
};

} // namespace vehicles
} // namespace game