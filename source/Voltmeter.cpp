#include <Voltmeter.hpp>

Voltmeter::Voltmeter() :
	Resistor("100000000000000000")
{
	setFilename("Voltmeter");

	mFirst->setPos(-Point::cRadius,
				   pixmap().height() / 2 - Point::cRadius);
	mSecond->setPos(pixmap().width() - Point::cRadius,
					pixmap().height()/2 - Point::cRadius);
}

void Voltmeter::setCurrent(const cpp_float& val)
{

}
