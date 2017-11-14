#include <Resistor.hpp>
#include <sstream>
#include <iomanip>

Resistor::Resistor(const std::string& resistance, Dimension dimension) :
	EObject(resistance, dimension),
	GObject("Resistor")
{
	mFirst->setPos(- Point::cRadius,
				   pixmap().height() / 2 - Point::cRadius);
	mSecond->setPos(pixmap().width() - Point::cRadius,
					pixmap().height() / 2 - Point::cRadius);
}

EObjectType Resistor::getType() const
{
	return EObjectType::Resistor;
}

void Resistor::setCurrent(const cpp_float& val)
{
	std::stringstream ss;
	ss
		<< std::fixed
		<< std::setprecision(std::numeric_limits<cpp_float>::digits10)
		<< val;
	mTextShow = QString::fromStdString( ss.str() );
	showText();
}
