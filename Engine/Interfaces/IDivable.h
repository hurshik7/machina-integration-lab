#pragma once

namespace engine {
namespace interfaces {

class IDivable
{
public:
	virtual ~IDivable() = default;
	virtual unsigned int GetDiveSpeed() const = 0;
};

} // namespace interfaces
} // namespace engine