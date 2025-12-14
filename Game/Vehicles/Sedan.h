#pragma once
#include "../../Engine/Vehicles/Vehicle.h"
#include "../../Engine/Vehicles/Interfaces/IDrivable.h"

namespace game {
namespace vehicles {

class Trailer;

class Sedan : public engine::vehicles::Vehicle, public engine::vehicles::interfaces::IDrivable
{
public:
	Sedan();
	Sedan(const Sedan& other);
	Sedan& operator=(const Sedan& rhs);
	virtual ~Sedan();

	bool AddTrailer(const Trailer* trailer);
	bool RemoveTrailer();
	virtual unsigned int GetMaxSpeed() const;
	virtual unsigned int GetDriveSpeed() const;
	virtual void TravelByMachina();

private:
	enum { IDLE_TIME = 1, MOVE_TIME = 5, IDLE_TIME_TRAIL_ON = 2 };
	bool mbIsTrailOn;
	const Trailer* mTrailer;
};

} // namespace vehicles
} // namespace game