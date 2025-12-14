#include "Trailer.h"

namespace game {
namespace vehicles {

Trailer::Trailer(unsigned int weight)
	: mWeight(weight)
{
}

Trailer::~Trailer()
{
}

unsigned int Trailer::GetWeight() const
{
	return mWeight;
}

} // namespace vehicles
} // namespace game