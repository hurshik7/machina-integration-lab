#pragma once

namespace engine {
namespace core {

struct TravelContext
{
	unsigned int hours;           // Travel duration in hours
	float weatherMultiplier;      // Weather impact (1.0 = normal conditions)
	bool isEmergency;             // Emergency mode (may skip idle time)

	// Default constructor with sensible defaults
	TravelContext()
		: hours(1)
		, weatherMultiplier(1.0f)
		, isEmergency(false)
	{
	}

	// Parameterized constructor
	TravelContext(unsigned int h, float weather = 1.0f, bool emergency = false)
		: hours(h)
		, weatherMultiplier(weather)
		, isEmergency(emergency)
	{
	}
};

} // namespace core
} // namespace engine
