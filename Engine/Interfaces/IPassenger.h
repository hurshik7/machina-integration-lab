#pragma once

#include <string>

namespace engine {
namespace interfaces {

class IPassenger
{
public:
	virtual ~IPassenger() = default;

	virtual const std::string& GetName() const = 0;
	virtual unsigned int GetWeight() const = 0;
};

} // namespace interfaces
} // namespace engine
