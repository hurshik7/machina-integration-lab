#include "Vehicle.h"
#include "../../Game/Vehicles/Person.h"

namespace engine {
namespace vehicles {

using game::vehicles::Person;

	Vehicle::Vehicle(unsigned int maxPassengersCount)
		: mMaxPassengersCount(maxPassengersCount)
		, mPassengersWeight(0)
		, mOdo(0)
		, mIdleTime(0)
		, mMoveTime(0)
	{
		mPassengers.reserve(mMaxPassengersCount);
	}

	Vehicle::~Vehicle() = default;

	Vehicle::Vehicle(Vehicle&& other) noexcept
		: mMaxPassengersCount(other.mMaxPassengersCount)
		, mPassengersWeight(other.mPassengersWeight)
		, mOdo(other.mOdo)
		, mIdleTime(other.mIdleTime)
		, mMoveTime(other.mMoveTime)
		, mPassengers(std::move(other.mPassengers))
	{
		other.mPassengersWeight = 0;
		other.mOdo = 0;
		other.mIdleTime = 0;
		other.mMoveTime = 0;
	}

	Vehicle& Vehicle::operator=(Vehicle&& rhs) noexcept
	{
		if (this == &rhs)
		{
			return *this;
		}

		mMaxPassengersCount = rhs.mMaxPassengersCount;
		mPassengersWeight = rhs.mPassengersWeight;
		mOdo = rhs.mOdo;
		mIdleTime = rhs.mIdleTime;
		mMoveTime = rhs.mMoveTime;
		mPassengers = std::move(rhs.mPassengers);

		rhs.mPassengersWeight = 0;
		rhs.mOdo = 0;
		rhs.mIdleTime = 0;
		rhs.mMoveTime = 0;

		return *this;
	}

	bool Vehicle::AddPassenger(std::unique_ptr<const Person> person)
	{
		if (mPassengers.size() >= mMaxPassengersCount)
		{
			return false;
		}

		mPassengersWeight += person->GetWeight();
		mPassengers.push_back(std::move(person));
		return true;
	}

	bool Vehicle::RemovePassenger(unsigned int i)
	{
		if (i >= mPassengers.size())
		{
			return false;
		}

		mPassengersWeight -= mPassengers[i]->GetWeight();
		mPassengers.erase(mPassengers.begin() + i);
		return true;
	}

	std::unique_ptr<const Person> Vehicle::ReleasePassenger(unsigned int i)
	{
		if (i >= mPassengers.size())
		{
			return nullptr;
		}

		mPassengersWeight -= mPassengers[i]->GetWeight();
		std::unique_ptr<const Person> released = std::move(mPassengers[i]);
		mPassengers.erase(mPassengers.begin() + i);
		return released;
	}

	unsigned int Vehicle::GetPassengersCount() const
	{
		return static_cast<unsigned int>(mPassengers.size());
	}

	unsigned int Vehicle::GetMaxPassengersCount() const
	{
		return mMaxPassengersCount;
	}

	const Person* Vehicle::GetPassenger(unsigned int i) const
	{
		if (i >= mPassengers.size())
		{
			return nullptr;
		}
		return mPassengers[i].get();
	}

	unsigned int Vehicle::GetPassengersWeight() const
	{
		return mPassengersWeight;
	}

	std::vector<std::unique_ptr<const Person>> Vehicle::ReleaseAllPassengers()
	{
		mPassengersWeight = 0;
		return std::move(mPassengers);
	}

	unsigned int Vehicle::GetOdo() const
	{
		return mOdo;
	}

	void Vehicle::AddOdo(unsigned int distance)
	{
		mOdo += distance;
	}

	unsigned int Vehicle::GetIdleTime() const
	{
		return mIdleTime;
	}

	void Vehicle:: AddIdleTime()
	{
		mIdleTime++;
	}

	void Vehicle::ResetIdleTIme()
	{
		mIdleTime = 0;
	}

	unsigned int Vehicle::GetMoveTime() const
	{
		return mMoveTime;
	}

	void Vehicle::AddMoveTime()
	{
		mMoveTime++;
	}

	void Vehicle::ResetMoveTime()
	{
		mMoveTime = 0;
	}

} // namespace vehicles
} // namespace engine
