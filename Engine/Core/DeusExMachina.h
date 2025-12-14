#pragma once

#include "../Vehicles/Vehicle.h"

namespace engine {
namespace core {

class DeusExMachina
{
public:
	static DeusExMachina* GetInstance();
	void Travel() const;
	bool AddVehicle(vehicles::Vehicle* vehicle);
	bool RemoveVehicle(unsigned int i);
	const vehicles::Vehicle* GetFurthestTravelled() const;

private:
	DeusExMachina() {};

	DeusExMachina(const DeusExMachina& other) = delete;
	DeusExMachina& operator=(const DeusExMachina& rhs) = delete;

	static DeusExMachina* mInstance;
	enum { MAX_VEHICLES_COUNT = 10 };
	vehicles::Vehicle** mVehicles;
	unsigned int mVehiclesCount;
};

} // namespace core
} // namespace engine
