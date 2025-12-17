#pragma once

#include <memory>
#include <vector>

#include "../Core/TravelContext.h"
#include "../Interfaces/IPassenger.h"

namespace engine {
namespace vehicles {

class Vehicle
{
public:
	Vehicle(unsigned int maxPassengersCount);
	virtual ~Vehicle();

	// Move-only
	Vehicle(const Vehicle&) = delete;
	Vehicle& operator=(const Vehicle&) = delete;
	Vehicle(Vehicle&& other) noexcept;
	Vehicle& operator=(Vehicle&& rhs) noexcept;

	virtual unsigned int GetMaxSpeed() const = 0;

	bool AddPassenger(std::unique_ptr<const engine::interfaces::IPassenger> passenger);
	bool RemovePassenger(unsigned int i);
	std::unique_ptr<const engine::interfaces::IPassenger> ReleasePassenger(unsigned int i);
	const engine::interfaces::IPassenger* GetPassenger(unsigned int i) const;
	unsigned int GetPassengersCount() const;
	unsigned int GetMaxPassengersCount() const;
	unsigned int GetPassengersWeight() const;
	std::vector<std::unique_ptr<const engine::interfaces::IPassenger>> ReleaseAllPassengers();

	unsigned int GetOdo() const;
	void AddOdo(unsigned int distance);
	unsigned int GetIdleTime() const;
	void AddIdleTime();
	void ResetIdleTIme();
	unsigned int GetMoveTime() const;
	void AddMoveTime();
	void ResetMoveTime();
	virtual void TravelByMachina(const core::TravelContext& context) = 0;

private:
	unsigned int mMaxPassengersCount;
	unsigned int mPassengersWeight;
	unsigned int mOdo;
	unsigned int mIdleTime;
	unsigned int mMoveTime;
	std::vector<std::unique_ptr<const engine::interfaces::IPassenger>> mPassengers;
};

} // namespace vehicles
} // namespace engine