#pragma once

namespace engine {
namespace capabilities {

class FlyingCapability
{
public:
	explicit FlyingCapability(unsigned int flySpeed);
	~FlyingCapability() = default;

	// Copyable
	FlyingCapability(const FlyingCapability&) = default;
	FlyingCapability& operator=(const FlyingCapability&) = default;

	unsigned int GetFlySpeed() const;
	void SetFlySpeed(unsigned int speed);

private:
	unsigned int mFlySpeed;
};

} // namespace capabilities
} // namespace engine
