#include "Sedan.h"
#include "Trailer.h"

namespace game {
namespace vehicles {

	Sedan::Sedan()
		: Vehicle(4)
		, mTrailer(nullptr)
	{
	}

	Sedan::~Sedan() = default;

	Sedan::Sedan(Sedan&& other) noexcept
		: Vehicle(std::move(other))
		, mTrailer(std::move(other.mTrailer))
	{
	}

	Sedan& Sedan::operator=(Sedan&& rhs) noexcept
	{
		if (this == &rhs)
		{
			return *this;
		}

		Vehicle::operator=(std::move(rhs));
		mTrailer = std::move(rhs.mTrailer);

		return *this;
	}

	bool Sedan::AddTrailer(std::unique_ptr<Trailer> trailer)
	{
		if (mTrailer != nullptr)
		{
			return false;
		}

		mTrailer = std::move(trailer);
		return true;
	}

	bool Sedan::RemoveTrailer()
	{
		if (mTrailer == nullptr)
		{
			return false;
		}

		mTrailer.reset();
		return true;
	}

	const Trailer* Sedan::GetTrailer() const
	{
		return mTrailer.get();
	}

	unsigned int Sedan::GetMaxSpeed() const
	{
		return GetDriveSpeed();
	}

	unsigned int Sedan::GetDriveSpeed() const
	{
		unsigned int ret;
		unsigned int totalWeight = GetPassengersWeight();
		if (mTrailer != nullptr)
		{
			totalWeight += mTrailer->GetWeight();
		}

		if (totalWeight <= 80)
		{
			ret = 480;
		}
		else if (totalWeight <= 160)
		{
			ret = 458;
		}
		else if (totalWeight <= 260)
		{
			ret = 400;
		}
		else if (totalWeight <= 350)
		{
			ret = 380;
		}
		else
		{
			ret = 300;
		}
		return ret;
	}

	void Sedan::TravelByMachina(const engine::core::TravelContext& /*context*/)
	{
		unsigned int moveTime = GetMoveTime();
		unsigned int speed = GetMaxSpeed();
		//check available
		if (moveTime < MOVE_TIME)
		{
			//move
			AddMoveTime();
			AddOdo(speed);
		}
		else if (moveTime == MOVE_TIME)
		{
			AddIdleTime();
			if (mTrailer != nullptr)
			{
				if (GetIdleTime() == IDLE_TIME_TRAIL_ON)
				{
					ResetIdleTIme();
					ResetMoveTime();
				}
			}
			else
			{
				if (GetIdleTime() == IDLE_TIME)
				{
					ResetMoveTime();
					ResetIdleTIme();
				}
			}
		}
	}

} // namespace vehicles
} // namespace game