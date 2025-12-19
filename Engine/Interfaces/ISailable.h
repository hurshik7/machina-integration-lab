#pragma once

namespace engine {
namespace interfaces {

class ISailable
{
public:
	virtual ~ISailable() = default;
	virtual unsigned int GetSailSpeed() const = 0;
};

} // namespace interfaces
} // namespace engine