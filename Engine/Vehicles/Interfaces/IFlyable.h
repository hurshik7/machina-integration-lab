#pragma once

namespace engine {
namespace vehicles {
namespace interfaces {

class IFlyable
{
public:
	virtual ~IFlyable() = default;
	virtual unsigned int GetFlySpeed() const = 0;
};

} // namespace interfaces
} // namespace vehicles
} // namespace engine