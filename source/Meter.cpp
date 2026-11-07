#include <Meter.hpp>

#include <QBrush>
#include <QFont>

// The display window of the `Ammeter`/`Voltmeter` sprites
static const qreal cDisplayRight = 360;
static const qreal cDisplayCenterY = 300;

Meter::Meter(const QString& file, const std::string& resistance) :
	Resistor(resistance)
{
	setFilename(file);

	mFirst->setPos(-Point::cRadius,
				   pixmap().height() / 2 - Point::cRadius);
	mSecond->setPos(pixmap().width() - Point::cRadius,
					pixmap().height() / 2 - Point::cRadius);

	QFont font;
	font.setPixelSize(64);

	mDisplay = new QGraphicsSimpleTextItem(this);
	mDisplay->setFont(font);
	mDisplay->setBrush( QColor(51, 51, 51) );
}

void Meter::getInput()
{
	// A reading isn't editable
}

void Meter::showValue(const cpp_float& value)
{
	mDisplay->setText( format(value) );

	const QRectF rect = mDisplay->boundingRect();
	mDisplay->setPos( cDisplayRight - rect.width(),
					  cDisplayCenterY - rect.height() / 2 );
}
