#include "DivingCapability.h"

namespace engine {
namespace capabilities {

DivingCapability::DivingCapability(unsigned int diveSpeed)
	: mDiveSpeed(diveSpeed)
{
}

unsigned int DivingCapability::GetDiveSpeed() const
{
	return mDiveSpeed;
}

void DivingCapability::SetDiveSpeed(unsigned int speed)
{
	mDiveSpeed = speed;
}

} // namespace capabilities
} // namespace engine
