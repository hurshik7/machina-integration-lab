#pragma once

#include <string>
#include "../../Engine/Interfaces/IPassenger.h"

namespace game {
namespace vehicles {

class Person : public engine::interfaces::IPassenger
{
public:
	Person(const char* name, unsigned int weight);
	virtual ~Person();

	virtual const std::string& GetName() const override;
	virtual unsigned int GetWeight() const override;

private:
	std::string mName;
	unsigned int mWeight;
};

} // namespace vehicles
} // namespace game