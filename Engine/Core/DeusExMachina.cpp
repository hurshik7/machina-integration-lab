#include "DeusExMachina.h"

namespace engine {
namespace core {

using vehicles::Vehicle;

	std::unique_ptr<DeusExMachina, DeusExMachina::InstanceDeleter> DeusExMachina::mInstance = nullptr;

	DeusExMachina* DeusExMachina::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance.reset(new DeusExMachina());
		}
		return mInstance.get();
	}

	void DeusExMachina::ResetInstance()
	{
		mInstance.reset();
	}

	void DeusExMachina::Travel(const TravelContext& context) const
	{
		for (const std::unique_ptr<vehicles::Vehicle>& vehicle : mVehicles)
		{
			vehicle->TravelByMachina(context);
		}
	}

	bool DeusExMachina::AddVehicle(std::unique_ptr<Vehicle> vehicle)
	{
		if (mVehicles.size() >= MAX_VEHICLES_COUNT)
		{
			return false;
		}

		mVehicles.push_back(std::move(vehicle));
		return true;
	}

	bool DeusExMachina::RemoveVehicle(unsigned int i)
	{
		if (i >= mVehicles.size())
		{
			return false;
		}

		mVehicles.erase(mVehicles.begin() + i);
		return true;
	}

	const Vehicle* DeusExMachina::GetFurthestTravelled() const
	{
		if (mVehicles.empty())
		{
			return nullptr;
		}

		const Vehicle* furthest = mVehicles[0].get();
		unsigned int maxDistance = furthest->GetOdo();

		for (const std::unique_ptr<vehicles::Vehicle>& vehicle : mVehicles)
		{
			if (vehicle->GetOdo() > maxDistance)
			{
				maxDistance = vehicle->GetOdo();
				furthest = vehicle.get();
			}
		}

		return furthest;
	}

	size_t DeusExMachina::GetVehicleCount() const
	{
		return mVehicles.size();
	}

} // namespace core
} // namespace engine