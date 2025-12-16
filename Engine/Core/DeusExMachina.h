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
	static void ResetInstance();

	void Travel(const TravelContext& context) const;
	bool AddVehicle(std::unique_ptr<vehicles::Vehicle> vehicle);
	bool RemoveVehicle(unsigned int i);
	const vehicles::Vehicle* GetFurthestTravelled() const;
	size_t GetVehicleCount() const;

private:
	struct InstanceDeleter
	{
		void operator()(DeusExMachina* ptr) const { delete ptr; }
	};
	friend struct InstanceDeleter;

	DeusExMachina() = default;
	~DeusExMachina() = default;

	DeusExMachina(const DeusExMachina& other) = delete;
	DeusExMachina& operator=(const DeusExMachina& rhs) = delete;

	static std::unique_ptr<DeusExMachina, InstanceDeleter> mInstance;
	static constexpr size_t MAX_VEHICLES_COUNT = 10;
	std::vector<std::unique_ptr<vehicles::Vehicle>> mVehicles;
};

} // namespace core
} // namespace engine
