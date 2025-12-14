#include "Person.h"

namespace game {
namespace vehicles {

	Person::Person(const char* name, unsigned int weight)
		: mName(name)
		, mWeight(weight)
	{
	}

	Person::~Person()
	{
	}

	const std::string& Person::GetName() const
	{
		return mName;
	}

	unsigned int Person::GetWeight() const
	{
		return mWeight;
	}

} // namespace vehicles
} // namespace game