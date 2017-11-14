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

	mInputWindow = new InputWindow("", "Ω");

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
}

EObjectType Resistor::getType() const
{
	return EObjectType::Resistor;
}

void Resistor::setCurrent(const cpp_float& val)
{
	if (val == cpp_float("0.0"));
/*
	else
	{
		std::stringstream ss;
		ss
			<< std::fixed
			<< std::setprecision(std::numeric_limits<cpp_float>::digits10)
			<< val;
		mTextShow = QString::fromStdString( ss.str() );
		showText();
	}
	*/
}

void Resistor::getInput()
{
	mInputWindow->show();
}

Resistor::~Resistor()
{
	delete mInputWindow;
}
