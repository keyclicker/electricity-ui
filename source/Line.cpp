#include <Line.hpp>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QGraphicsScene>
#include <QLinearGradient>
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QList>
#include <Canvas.h>
#include <GObject.h>

#define VIEW this->scene()->views().first()
#define CANVAS dynamic_cast<Canvas*>(VIEW)

Line::Line(QPointF pos,
		   int grid) :
	cLineWidth(26.f),
	cGridSize(grid),
	mDifference(0, 0)
{
	mFirst = new Point(cGridSize, this);
	mSecond = new Point(cGridSize, this);
	mFirst->setPos(pos);
	mSecond->setPos(pos);

	mFirst->setAcceptHoverEvents(true);
	mFirst->setFlag(ItemIsMovable);

	mSecond->setAcceptHoverEvents(true);
	mSecond->setFlag(ItemIsMovable);

	mSecond->moveBy(cGridSize, 0.f);

	mFirst->normalize();
	mSecond->normalize();

	setAcceptHoverEvents(true);
	setFlags(ItemIsMovable | ItemIsFocusable);

	QPen linePen;
	linePen.setStyle(Qt::SolidLine);
	linePen.setCapStyle(Qt::RoundCap);
	linePen.setColor( QColor(69, 130, 120) );
	linePen.setWidthF(cLineWidth);

	this->setPen(linePen);
	updateLine();
}

Line::Line(QPoint p1, QPoint p2) :
	cGridSize(50),
	cLineWidth(26.f),
	mDifference(0.f, 0.f)
{
	mFirst = new Point(cGridSize, this);
	mSecond = new Point(cGridSize, this);
	mFirst->setPos( p1 - QPoint(Point::cRadius, Point::cRadius) );
	mSecond->setPos( p2 - QPoint(Point::cRadius, Point::cRadius) );

	mFirst->setAcceptHoverEvents(true);
	mFirst->setFlag(ItemIsMovable);

	mSecond->setAcceptHoverEvents(true);
	mSecond->setFlag(ItemIsMovable);

	setAcceptHoverEvents(true);
	setFlags(ItemIsMovable | ItemIsFocusable);

	QPen linePen;
	linePen.setStyle(Qt::SolidLine);
	linePen.setCapStyle(Qt::RoundCap);
	linePen.setColor( QColor(69, 130, 120) );
	linePen.setWidthF(cLineWidth);

	this->setPen(linePen);
	updateLine();
}

void Line::updateLine()
{
	this->setLine( QLineF( mFirst->pos() + QPointF(Point::cRadius, Point::cRadius),
						   mSecond->pos() + QPointF(Point::cRadius, Point::cRadius) ) );
}

void Line::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsLineItem::mouseReleaseEvent(event);
	normalize();
}

void Line::normalize()
{
	const float step = cGridSize;

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

void Line::startDrawing()
{
	// The second end follows the cursor until a click drops it
	CANVAS->setDrag(true);
	this->setZValue(1.1);

	connect( CANVAS, SIGNAL( cursorChangePos(QPointF) ),
			 this, SLOT( movePoint(QPointF) )
	);
}

void Line::pointReleased()
{
	const bool wasDrawing =
		disconnect( CANVAS, SIGNAL( cursorChangePos(QPointF) ),
					this, SLOT( movePoint(QPointF) )
		);

	if (wasDrawing)
	{
		CANVAS->setDrag(false);
		this->setZValue(0);
	}

	// A wire of zero length would short its pin to itself
	if ( mFirst->pos() == mSecond->pos() )
		remove();
}

void Line::movePoint(QPointF point)
{
	// Center the end on the cursor, so the next click lands on it
	mSecond->setPos( mapFromScene(point) -
					 QPointF(Point::cRadius, Point::cRadius) );
}

int Line::type() const
{
	return static_cast<int>(GObjectType::Line);
}

void Line::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Delete)
	{
		CANVAS->setDrag(false);
		remove();
	}
}

void Line::remove()
{
	this->scene()->removeItem(this);
	this->deleteLater();
}

void Line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	static auto zVal = this->zValue();

	if(event->button() == Qt::LeftButton)
	{
		CANVAS->setDrag( !CANVAS->isDrag() );

		if (CANVAS->isDrag())
		{
			connect( CANVAS, SIGNAL( cursorChangePos(QPointF) ),
					 this, SLOT( moveTo( QPointF) )
			);

			this->setZValue(1.1);

			mDifference = mapToScene(event->pos()) - this->pos();
		}
		else
		{
			disconnect( CANVAS, SIGNAL( cursorChangePos(QPointF) ),
						this, SLOT( moveTo(QPointF) )
			);

			this->setZValue(zVal);
			normalize();
		}
	}
}

void Line::moveTo(QPointF point)
{
	this->setPos(point - mDifference);
}

void Line::setCurrent(QPoint p)
{
	if (p == mFirst->pos().toPoint());

}

#undef VIEW
#undef CANVAS
