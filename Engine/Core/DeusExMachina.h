#pragma once

#include <memory>
#include <vector>

#include "TravelContext.h"
#include "../Vehicles/Vehicle.h"

namespace engine {
namespace core {

class DeusExMachina
{
public:
	static DeusExMachina* GetInstance();
	void Travel(const TravelContext& context) const;
	bool AddVehicle(std::unique_ptr<vehicles::Vehicle> vehicle);
	bool RemoveVehicle(unsigned int i);
	const vehicles::Vehicle* GetFurthestTravelled() const;
	size_t GetVehicleCount() const;

private:
	DeusExMachina() {};

	DeusExMachina(const DeusExMachina& other) = delete;
	DeusExMachina& operator=(const DeusExMachina& rhs) = delete;

	static DeusExMachina* mInstance;
	static constexpr size_t MAX_VEHICLES_COUNT = 10;
	std::vector<std::unique_ptr<vehicles::Vehicle>> mVehicles;
};

} // namespace core
} // namespace engine
