#ifndef INDUCTOR_HPP_INCLUDED
#define INDUCTOR_HPP_INCLUDED

#include <EObject.hpp>
#include <Counter.hpp>

class Inductor : public EObject,
                 public Counter<Inductor>
{
    public:
		Inductor(const std::string&, Dimension = Dimension::Normal);
		EObjectType getType() const override;
};

#endif
