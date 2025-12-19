#pragma once

namespace engine {
namespace interfaces {

class IDrivable
{
public:
	virtual ~IDrivable() = default;
	virtual unsigned int GetDriveSpeed() const = 0;
};

} // namespace interfaces
} // namespace engine