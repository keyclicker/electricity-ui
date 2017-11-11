#ifndef RESISTOR_HPP_INCLUDED
#define RESISTOR_HPP_INCLUDED

#include <EObject.hpp>
#include <Counter.hpp>

#include <string>

class Resistor : public EObject,
                 public Counter<Resistor>
{
    public:
		Resistor(const std::string&, Dimension = Dimension::Normal);
        EObjectType getType() const override;
};

#endif
