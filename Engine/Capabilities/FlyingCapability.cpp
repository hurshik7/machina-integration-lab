#include "FlyingCapability.h"

namespace engine {
namespace capabilities {

FlyingCapability::FlyingCapability(unsigned int flySpeed)
	: mFlySpeed(flySpeed)
{
}

unsigned int FlyingCapability::GetFlySpeed() const
{
	return mFlySpeed;
}

void FlyingCapability::SetFlySpeed(unsigned int speed)
{
	mFlySpeed = speed;
}

} // namespace capabilities
} // namespace engine
