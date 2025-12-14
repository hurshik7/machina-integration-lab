#pragma once

namespace game {
namespace vehicles {

class Trailer
{
public:
	Trailer(unsigned int weight);
	virtual ~Trailer();

	unsigned int GetWeight() const;

private:
	unsigned int mWeight;
};

} // namespace vehicles
} // namespace game