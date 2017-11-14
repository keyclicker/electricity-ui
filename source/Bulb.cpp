#include <Bulb.hpp>

Bulb::Bulb(const std::string& val, Dimension d) :
	Resistor(val, d)
{
	setFilename("Bulb_off");

	mFirst->setPos(-Point::cRadius + 150,
				   pixmap().height() / 2 - Point::cRadius);
	mSecond->setPos(-Point::cRadius + pixmap().width() - 150,
					pixmap().height() / 2 - Point::cRadius);
}

void Bulb::setCurrent(const cpp_float& val)
{
	if ( val != cpp_float("0.0") )
		setFilename("Bulb_on");
	else
	{

		setFilename("Bulb_off");
	}
}

