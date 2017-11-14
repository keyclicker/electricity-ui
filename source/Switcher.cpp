#include <Switcher.hpp>

const cpp_float Switch::ON("1.0");
const cpp_float Switch::OFF("0.0");

Switch::Switch(bool state) :
	EObject("1.0"),
	GObject("Switch_on")
{
	if (state)
		setValue("1.0");
	else
		setValue("0.0");

	mFirst->setPos(- Point::cRadius,
				   pixmap().height() / 2 - Point::cRadius);
	mSecond->setPos(pixmap().width() - Point::cRadius,
					pixmap().height() / 2 - Point::cRadius);
}

EObjectType Switch::getType() const
{
	return EObjectType::Switch;
}


void Switch::setState(bool state)
{
	if (state)
	{
		setFilename("Switch_on");
		setValue("1.0");
	}
	else
	{
		setFilename("Switch_off");
		setValue("0.0");
	}
}

void Switch::setCurrent(const cpp_float& val)
{

}

void Switch::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	if (getValue() == Switch::ON)
		setState(false);
	else
		setState(true);
}
