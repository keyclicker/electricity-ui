#ifndef VOLTMETER_HPP_INCLUDED
#define VOLTMETER_HPP_INCLUDED

#include <Meter.hpp>

class Voltmeter : public Meter
{
	public:
		Voltmeter();
		EObjectType getType() const override;
		void setCurrent(const cpp_float&) final;
};

#endif
