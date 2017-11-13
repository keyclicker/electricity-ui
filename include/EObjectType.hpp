#ifndef EOBJECTTYPE_HPP_INCLUDED
#define EOBJECTTYPE_HPP_INCLUDED

#include <cstdint>

enum class EObjectType : std::size_t
{
    Resistor = 82,
    SourceOfElectricity = 69,
	SourceOfCurrent = 73,
    Capacitor = 67,
	Inductor = 76,
	Switch = 83
};

#endif
