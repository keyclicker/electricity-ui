#include <Resistor.hpp>

Resistor::Resistor(double resistance, Dimension dimension) :
	EObject(resistance, dimension)
{

}

EObjectType Resistor::getType() const
{
	return EObjectType::Resistor;
}
