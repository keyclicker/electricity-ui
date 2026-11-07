#include <Point.hpp>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <GObject.h>

#include <algorithm>
#include <cmath>

#include "Line.hpp"
#include "Canvas.h"

#define VIEW this->scene()->views().first()
#define CANVAS dynamic_cast<Canvas*>(VIEW)

const qreal Point::cRadius = 18.f;

Point::Point(int grid,
			 QGraphicsItem* parent) :
	QGraphicsItem(parent),
	cGridSize(grid),
	mHover(false)
{
	this->setZValue(1.f);
	this->setFlag(ItemSendsGeometryChanges);

	mHoverBrush.setStyle(Qt::SolidPattern);
	mHoverBrush.setColor(Qt::red);
	mHoverPen.setColor(Qt::red);

	setTransformOriginPoint(Point::cRadius, Point::cRadius);

	mDefPen.setColor( QColor(125, 125, 125) );
	mDefBrush.setColor( QColor(125, 125, 125) );
	mDefBrush.setStyle(Qt::SolidPattern);
}

QRectF Point::boundingRect() const
{
	return QRectF(0, 0,Point::cRadius * 2, Point::cRadius * 2);
}

QPainterPath Point::shape() const
{
	QPainterPath path;
	path.addEllipse(boundingRect());
	return path;
}

void Point::paint(QPainter* painter,
				  const QStyleOptionGraphicsItem* style,
				  QWidget* wgt)
{
	if (mHover)
	{
		painter->setBrush(mHoverBrush);
		painter->setPen(mHoverPen);
	}
	else
	{
		painter->setPen(mDefPen);
		painter->setBrush(mDefBrush);
	}


	painter->drawEllipse(boundingRect());
}

void Point::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
	normalize();
}

void Point::normalize()
{
	const int step = cGridSize;

		qreal curX = std::floor( (pos().x() + Point::cRadius) / step );
		qreal curY = std::floor( (pos().y() + Point::cRadius) / step );

	qreal x = pos().x() + Point::cRadius;
	qreal y = pos().y() + Point::cRadius;

	qreal l[] = {
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


	moveBy( -Point::cRadius, -Point::cRadius );
	update();
}

void Point::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		Line* l = new Line(this->pos() -
			QPointF(Point::cRadius, Point::cRadius), CANVAS->cGridSize);

		this->scene()->addItem(l);
	}
}

QVariant Point::itemChange(GraphicsItemChange change,
						   const QVariant& value)
{
	// A wire is drawn between its two points: redraw it when one moves
	if ( change == ItemPositionHasChanged && parentItem() &&
		 parentItem()->type() == static_cast<int>(GObjectType::Line) )
		static_cast<Line*>( parentItem() )->updateLine();

	return QGraphicsItem::itemChange(change, value);
}

int Point::type() const
{
	return static_cast<int>(GObjectType::Point);
}

void Point::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	mHover = true;
	update();
	QGraphicsItem::hoverEnterEvent(event);
}

void Point::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	mHover = false;
	update();
	QGraphicsItem::hoverLeaveEvent(event);
}

#undef VIEW
#undef SCENE
