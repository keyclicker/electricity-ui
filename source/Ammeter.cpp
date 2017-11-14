#include <Ammeter.hpp>

Ammeter::Ammeter() :
	Resistor("0.0")
{
	setFilename("Ammeter");

	mFirst->setPos(-Point::cRadius,
				   pixmap().height() / 2 - Point::cRadius);
	mSecond->setPos(pixmap().width() - Point::cRadius,
					pixmap().height()/2 - Point::cRadius);
	mInputWindow->close();
}

void Ammeter::setCurrent(const cpp_float& val)
{

}

void Ammeter::getInput()
{

}
