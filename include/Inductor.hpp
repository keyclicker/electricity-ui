#ifndef INDUCTOR_HPP_INCLUDED
#define INDUCTOR_HPP_INCLUDED

#include <EObject.hpp>
#include <Counter.hpp>

class Inductor : public EObject,
                 public Counter<Inductor>
{
    public:
		Inductor(double, Dimension = Dimension::Normal);
        EObjectType getType() const;
};

#endif // INDUCTOR_HPP_INCLUDED
