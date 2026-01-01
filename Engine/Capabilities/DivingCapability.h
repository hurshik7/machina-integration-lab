#pragma once

namespace engine {
namespace capabilities {

class DivingCapability
{
public:
	explicit DivingCapability(unsigned int diveSpeed);
	~DivingCapability() = default;

	// Copyable
	DivingCapability(const DivingCapability&) = default;
	DivingCapability& operator=(const DivingCapability&) = default;

	unsigned int GetDiveSpeed() const;
	void SetDiveSpeed(unsigned int speed);

private:
	unsigned int mDiveSpeed;
};

} // namespace capabilities
} // namespace engine
