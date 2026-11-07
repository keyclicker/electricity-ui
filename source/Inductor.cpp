#include <Inductor.hpp>

Inductor::Inductor(const std::string& induction, Dimension dimension) :
	EObject(induction, dimension),
	GObject("Inductor")
{
	mFirst->setPos(- Point::cRadius + 250,
				   pixmap().height() / 2 - Point::cRadius);
	mSecond->setPos(pixmap().width() - Point::cRadius - 250,
					pixmap().height() / 2 - Point::cRadius);

	mInputWindow = new InputWindow("", "H");

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

EObjectType Inductor::getType() const
{
	return EObjectType::Inductor;
}

void Inductor::getInput()
{
	mInputWindow->show();
}

void Inductor::setCurrent(const cpp_float& val)
{
	showCurrent(val);
}

Inductor::~Inductor()
{
	delete mInputWindow;
}


