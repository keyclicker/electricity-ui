#ifndef VOLTMETER_HPP_INCLUDED
#define VOLTMETER_HPP_INCLUDED

#include <Resistor.hpp>

class Voltmeter : public Resistor
{
	public:
		Voltmeter();
		void setCurrent(const cpp_float&) final;
};

#endif
