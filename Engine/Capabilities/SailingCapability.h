#pragma once

namespace engine {
namespace capabilities {

class SailingCapability
{
public:
	explicit SailingCapability(unsigned int sailSpeed);
	~SailingCapability() = default;

	// Copyable
	SailingCapability(const SailingCapability&) = default;
	SailingCapability& operator=(const SailingCapability&) = default;

	unsigned int GetSailSpeed() const;
	void SetSailSpeed(unsigned int speed);

private:
	unsigned int mSailSpeed;
};

} // namespace capabilities
} // namespace engine
