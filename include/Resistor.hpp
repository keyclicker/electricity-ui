#ifndef RESISTOR_HPP_INCLUDED
#define RESISTOR_HPP_INCLUDED

#include <EObject.hpp>
#include <Counter.hpp>
#include <GObject.h>

#include <string>

class Resistor : public EObject,
				 public GObject,
                 public Counter<Resistor>
{
    public:
		Resistor(const std::string& = "5", Dimension = Dimension::Normal);
        EObjectType getType() const override;
		void setCurrent(const cpp_float&) override;
};

#endif
