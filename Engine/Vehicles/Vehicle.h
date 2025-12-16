#pragma once

#include <memory>
#include <vector>

#include "../Core/TravelContext.h"

// Forward declaration to avoid circular dependency
namespace game {
namespace vehicles {
	class Person;
}
}

namespace engine {
namespace vehicles {

class Vehicle
{
public:
	Vehicle(unsigned int maxPassengersCount);
	virtual ~Vehicle();
	Vehicle(const Vehicle& other);
	Vehicle& operator=(const Vehicle& rhs);

	virtual unsigned int GetMaxSpeed() const = 0;

	bool AddPassenger(std::unique_ptr<const game::vehicles::Person> person);
	bool RemovePassenger(unsigned int i);
	std::unique_ptr<const game::vehicles::Person> ReleasePassenger(unsigned int i);
	const game::vehicles::Person* GetPassenger(unsigned int i) const;
	unsigned int GetPassengersCount() const;
	unsigned int GetMaxPassengersCount() const;
	unsigned int GetPassengersWeight() const;
	std::vector<std::unique_ptr<const game::vehicles::Person>> ReleaseAllPassengers();

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
	std::vector<std::unique_ptr<const game::vehicles::Person>> mPassengers;
};

} // namespace vehicles
} // namespace engine