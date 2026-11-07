#include <GObject.h>
#include <Canvas.h>

#include <QtGlobal>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMoveEvent>
#include <QKeyEvent>

#define VIEW this->scene()->views().first()
#define CANVAS dynamic_cast<Canvas*>(VIEW)

const QString GObject::sPrefix = ":/icons/icons/";
const QString GObject::sFormat = ".png";

GObject::GObject(const QString& file, QGraphicsItem* parent) :
	QGraphicsPixmapItem(parent),
	cFilename(file)
{
	QPixmap pixmap;

		if ( !pixmap.load(sPrefix + cFilename + sFormat) )
			qDebug() << "can't load";

	this->setPixmap( pixmap );
	this->setAcceptHoverEvents(true);
	this->setFlags(ItemIsMovable | ItemIsFocusable);

	mFirst = new Point(50, this);
	mSecond = new Point(50, this);
	mFirst->setAcceptHoverEvents(true);
	mSecond->setAcceptHoverEvents(true);
	this->mDifference = QPointF( pixmap.width() / 2,
								 pixmap.height() / 2);
}

void GObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	static auto zVal = this->zValue();

	if(event->button() == Qt::LeftButton)
	{
		// An element can't be dropped onto another one
		if ( CANVAS->isDrag() && isColliding() )
			return;

		CANVAS->setDrag( !CANVAS->isDrag() );

		if (CANVAS->isDrag())
		{
			connect( CANVAS, SIGNAL( cursorChangePos(QPointF) ),
					 this, SLOT( moveTo( QPointF) )
			);

			this->setZValue(1.1);

			this->setPixmap( QPixmap(sPrefix + cFilename +
									 "_drag" + sFormat) );

			mDifference = mapToScene(event->pos()) - this->pos();
		}
		else
		{
			disconnect( CANVAS, SIGNAL( cursorChangePos(QPointF) ),
						this, SLOT( moveTo(QPointF) )
			);

			this->setZValue(zVal);
			this->setPixmap( QPixmap(sPrefix + cFilename + sFormat) );
			normalize();
		}
	}

	if (CANVAS->isDrag() && event->button() == Qt::RightButton)
    {
		setAngle( this->rotation() + 90 );

		mDifference = QPoint( pixmap().width() / 2,
							  pixmap().height() / 2);

		QCursor::setPos(
						VIEW->mapToGlobal(
						VIEW->mapFromScene( pos() + QPoint(pixmap().width() / 2,
														   pixmap().height() / 2) )
					)
		);
    }
	else if (!CANVAS->isDrag() && event->button() == Qt::RightButton)
		getInput();

}

void GObject::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Delete)
    {
		CANVAS->setDrag(false);
		this->scene()->removeItem(this);
		this->deleteLater();
	}
}

void GObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	if ( !CANVAS->isDrag() )
	{

	}
}

void GObject::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

}


void GObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
}

void GObject::moveTo(QPointF point)
{
	this->setVisible(true);

	if ( isColliding() )
		this->setPixmap( QPixmap(sPrefix + cFilename + "_collision" + sFormat) );
    else
		this->setPixmap( QPixmap(sPrefix + cFilename + "_drag" + sFormat) );

	this->setPos(point - mDifference);
}

void GObject::setAngle(qreal angle)
{
	this->setTransformOriginPoint( pixmap().width() / 2,
								   pixmap().height() / 2 );
	this->setRotation(angle);

	// Keep the pins unrotated: the solver joins them by scenePos()
	mFirst->setRotation(-angle);
	mSecond->setRotation(-angle);
}

bool GObject::isColliding() const
{
	for ( const auto& i : collidingItems() )
		if ( i->type() == static_cast<int>(GObjectType::Item) )
			return true;

	return false;
}

int GObject::type() const
{
	return static_cast<int>(GObjectType::Item);
}

void GObject::normalize()
{
	const float step = 50;

		float curX = std::floor( (pos().x() ) / step );
		float curY = std::floor( (pos().y() ) / step );

	float x = pos().x();
	float y = pos().y();

	float l[] = {
		std::hypot(curX * step - x, curY * step - y),
		std::hypot(curX * step - x + step, curY * step - y),
		std::hypot(curX * step - x, curY * step - y + step),
		std::hypot(curX * step - x + step, curY * step - y + step)
	};

	const auto maxPos = std::distance( std::begin(l),
		std::min_element( std::begin(l), std::end(l) ) );

		switch(maxPos)
		{
			case 0:
			{
				setPos(curX * step, curY * step);
				break;
			}

			case 1:
			{
				setPos(curX * step + step, curY * step);
				break;
			}

			case 2:
			{
				setPos(curX * step, curY * step + step);
				break;
			}

			case 3:
			{
				setPos(curX * step + step, curY * step + step);
				break;
			}
		}

	update();
}

void GObject::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
	normalize();
}

void GObject::setFilename(const QString& name)
{
	cFilename = name;
	setPixmap(sPrefix + cFilename + sFormat);
}

void GObject::showCurrent(const cpp_float& current)
{
	// The solver's result, on hover
	setToolTip( "I = " + format( abs(current) ) + " A" );
}

QString GObject::format(const cpp_float& value)
{
	return QString::number( value.convert_to<double>(), 'g', 4 );
}

void GObject::getInput()
{

}


#undef VIEW
#undef CANVAS
