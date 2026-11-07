#include <Capacitor.hpp>

Capacitor::Capacitor(const std::string& capacity, Dimension dim) :
	EObject(capacity, dim),
	GObject("Capacitor")
{
	mFirst->setPos(- Point::cRadius + 100,
				   pixmap().height() / 2 - Point::cRadius);
	mSecond->setPos(pixmap().width() - Point::cRadius - 100,
					pixmap().height() / 2 - Point::cRadius);

	mInputWindow = new InputWindow("", "F");

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

EObjectType Capacitor::getType() const
{
	return EObjectType::Capacitor;
}

void Capacitor::getInput()
{
	mInputWindow->setInput( getString(), getDimensionType() );
	mInputWindow->show();
}

void Capacitor::setCurrent(const cpp_float& val)
{
	showCurrent(val);
}

Capacitor::~Capacitor()
{
	delete mInputWindow;
}
