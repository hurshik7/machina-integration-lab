#include "DrivingCapability.h"

namespace engine {
namespace capabilities {

DrivingCapability::DrivingCapability(unsigned int driveSpeed)
	: mDriveSpeed(driveSpeed)
{
}

unsigned int DrivingCapability::GetDriveSpeed() const
{
	return mDriveSpeed;
}

void DrivingCapability::SetDriveSpeed(unsigned int speed)
{
	mDriveSpeed = speed;
}

} // namespace capabilities
} // namespace engine
