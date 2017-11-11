#include <Switcher.hpp>

const cpp_float Switch::ON("1.0");
const cpp_float Switch::OFF("0.0");

Switch::Switch(bool state) :
	EObject("1.0")
{
	if (state)
		setValue("1.0");
	else
		setValue("0.0");
}

EObjectType Switch::getType() const
{
	return EObjectType::Switch;
}


void Switch::setState(bool state)
{
	if (state)
		setValue("1.0");
	else
		setValue("0.0");
}
