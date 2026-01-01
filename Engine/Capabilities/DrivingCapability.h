#pragma once

namespace engine {
namespace capabilities {

class DrivingCapability
{
public:
	explicit DrivingCapability(unsigned int driveSpeed);
	~DrivingCapability() = default;

	// Copyable
	DrivingCapability(const DrivingCapability&) = default;
	DrivingCapability& operator=(const DrivingCapability&) = default;

	unsigned int GetDriveSpeed() const;
	void SetDriveSpeed(unsigned int speed);

private:
	unsigned int mDriveSpeed;
};

} // namespace capabilities
} // namespace engine
