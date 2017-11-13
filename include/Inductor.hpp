#ifndef INDUCTOR_HPP_INCLUDED
#define INDUCTOR_HPP_INCLUDED

#include <GObject.h>
#include <EObject.hpp>
#include <Counter.hpp>

class Inductor : public EObject,
				 public GObject,
                 public Counter<Inductor>
{
    public:
		Inductor(const std::string& = "1", Dimension = Dimension::Nano);
		EObjectType getType() const override;
};

#endif
