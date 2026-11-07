#include <SourceOfElectricity.hpp>
#include <stdexcept>

SourceOfElectricity::SourceOfElectricity( const std::string& voltage,
										  char direction,
										  Dimension dimension) :
	EObject(voltage, dimension),
	mDirection(direction),
	GObject("Battery")
{
	if (direction != '+' && direction != '-')
		throw std::logic_error("SrcOfEl::SrcOfEl(): "
							   "Direction can be only + or - ");

	mFirst->setPos(- Point::cRadius,
				   pixmap().height() / 2 - Point::cRadius);
	mSecond->setPos(pixmap().width() - Point::cRadius,
					pixmap().height() / 2 - Point::cRadius);

	mInputWindow = new InputWindow("", "V");

	connect(mInputWindow, &InputWindow::getVal,
			[this](const auto& val)
			{
				this->setValue(val);
			}
	);

	connect(mInputWindow, &InputWindow::getDimension,
			[this](const auto& val)
			{
				this->setDimension(val);
			}
	);

	connect(mInputWindow, &InputWindow::accepted,
			[this]()
			{
				this->changed();
			}
	);
}

SourceOfElectricity::~SourceOfElectricity()
{
	delete mInputWindow;
}

EObjectType SourceOfElectricity::getType() const
{
    return EObjectType::SourceOfElectricity;
}

int SourceOfElectricity::getDirection() const
{
	return (mDirection == '+')? 1 : -1;
}

void SourceOfElectricity::setDirection(char direction)
{
	if (direction != '+' && direction != '-')
		throw std::logic_error("SrcOfEl::setDirection(char):"
							   "Direction can be only + or - ");

	mDirection = direction;
}

void SourceOfElectricity::setDirection(const Point* p)
{
	if (p->scenePos().toPoint() == mFirst->scenePos().toPoint())
		mDirection = '+';
	else
		mDirection = '-';
}

void SourceOfElectricity::getInput()
{
	mInputWindow->setInput( getString(), getDimensionType() );
	mInputWindow->show();
}

void SourceOfElectricity::setCurrent(const cpp_float& val)
{
	showCurrent(val);
}
