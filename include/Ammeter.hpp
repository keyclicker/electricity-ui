#ifndef AMMETER_HPP_INCLUDED
#define AMMETER_HPP_INCLUDED

#include <Meter.hpp>

class Ammeter : public Meter
{
	public:
		Ammeter();
		EObjectType getType() const override;
		void setCurrent(const cpp_float&) final;
};

#endif
