#pragma once

#include <string>

namespace game {
namespace vehicles {

class Person
{
public:
	Person(const char* name, unsigned int weight);
	virtual ~Person();

	const std::string& GetName() const;
	unsigned int GetWeight() const;

private:
	std::string mName;
	unsigned int mWeight;
};

} // namespace vehicles
} // namespace game