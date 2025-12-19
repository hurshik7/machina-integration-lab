#pragma once

namespace engine {
namespace interfaces {

class IFlyable
{
public:
	virtual ~IFlyable() = default;
	virtual unsigned int GetFlySpeed() const = 0;
};

} // namespace interfaces
} // namespace engine