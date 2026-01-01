#include "SailingCapability.h"

namespace engine {
namespace capabilities {

SailingCapability::SailingCapability(unsigned int sailSpeed)
	: mSailSpeed(sailSpeed)
{
}

unsigned int SailingCapability::GetSailSpeed() const
{
	return mSailSpeed;
}

void SailingCapability::SetSailSpeed(unsigned int speed)
{
	mSailSpeed = speed;
}

} // namespace capabilities
} // namespace engine
