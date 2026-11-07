#ifndef BULB_HPP_INCLUDED
#define BULB_HPP_INCLUDED

#include <Resistor.hpp>

class Bulb : public Resistor
{
	public:
		Bulb(const std::string& = "5", Dimension = Dimension::Normal);
		EObjectType getType() const override;
		void setCurrent(const cpp_float&) final;
};

#endif
