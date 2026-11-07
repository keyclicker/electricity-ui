#include <Voltmeter.hpp>

Voltmeter::Voltmeter() :
	Meter("Voltmeter", "100000000000000000")
{

}

EObjectType Voltmeter::getType() const
{
	return EObjectType::Voltmeter;
}

void Voltmeter::setCurrent(const cpp_float& val)
{
	// Its own tiny current times its huge resistance
	showValue( abs(val * getValue()) );
}
