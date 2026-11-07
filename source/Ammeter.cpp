#include <Ammeter.hpp>

Ammeter::Ammeter() :
	Meter("Ammeter", "0.0")
{

}

EObjectType Ammeter::getType() const
{
	return EObjectType::Ammeter;
}

void Ammeter::setCurrent(const cpp_float& val)
{
	showValue( abs(val) );
}
