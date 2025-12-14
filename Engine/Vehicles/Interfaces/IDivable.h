#pragma once

namespace engine {
namespace vehicles {
namespace interfaces {

class IDivable
{
public:
	virtual ~IDivable() = default;
	virtual unsigned int GetDiveSpeed() const = 0;
};

} // namespace interfaces
} // namespace vehicles
} // namespace engine