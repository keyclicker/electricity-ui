#ifndef AMMETER_HPP_INCLUDED
#define AMMETER_HPP_INCLUDED

#include <Resistor.hpp>

class Ammeter : public Resistor
{
	public:
		Ammeter();
		void setCurrent(const cpp_float&) final;
		void getInput() final;
};

#endif
