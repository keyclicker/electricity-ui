#include <Resistor.hpp>

Resistor::Resistor(const std::string& resistance, Dimension dimension) :
	EObject(resistance, dimension)
{

}

EObjectType Resistor::getType() const
{
	return EObjectType::Resistor;
}
