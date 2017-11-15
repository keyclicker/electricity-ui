#include <Line.hpp>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <GObject.h>
#include "Canvas.h"

#define VIEW this->scene()->views().first()
#define CANVAS dynamic_cast<Canvas*>(VIEW)

Line::Line(QPointF pos,
		   int grid) :
	cLineWidth(26.f),
	cGridSize(grid)
{
	mFirst = new Point(cGridSize, this);
	mSecond = new Point(cGridSize, this);
	mFirst->setPos(pos);
	mSecond->setPos(pos);

	mFirst->setAcceptHoverEvents(true);
	mFirst->setFlags(ItemIsMovable);

	mSecond->setAcceptHoverEvents(true);
	mSecond->setFlags(ItemIsMovable);

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

	this->setLine( QLineF( mFirst->pos() + QPointF(Point::cRadius, Point::cRadius),
						   mSecond->pos() + QPointF(Point::cRadius, Point::cRadius) ) );


	connect(VIEW, SIGNAL(cursorChangePos(QPointF)), this, SLOT(movePoint(QPointF)));
}

void Line::paint(QPainter* painter,
				 const QStyleOptionGraphicsItem* style,
				 QWidget* wgt)
{
	this->setLine( QLineF( mFirst->pos() + QPointF(Point::cRadius, Point::cRadius),
						   mSecond->pos() + QPointF(Point::cRadius, Point::cRadius) ) );

	QGraphicsLineItem::paint(painter, style, wgt);
}

void Line::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsLineItem::mouseReleaseEvent(event);

	disconnect(CANVAS, SIGNAL(cursorChangePos(QPointF)), this, SLOT(movePoint(QPointF)));

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

void Line::movePoint(QPointF point)
{
	this->mSecond->setPos(point);
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
		this->scene()->removeItem(this);
	}
}

#undef VIEW
#undef CANVAS
