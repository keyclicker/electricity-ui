#include <Line.hpp>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QGraphicsScene>
#include <QLinearGradient>
#include <GObject.h>

Line::Line(QPointF pos,
		   int grid) :
	cLineWidth(15.f),
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
	setFlag(ItemIsMovable);

	QPen linePen;
	linePen.setStyle(Qt::SolidLine);
	linePen.setCapStyle(Qt::RoundCap);
	linePen.setColor( QColor(69, 130, 120) );
	linePen.setWidthF(cLineWidth);

	this->setPen(linePen);

	this->setLine( QLineF( mFirst->pos() + QPointF(Point::cRadius, Point::cRadius),
						   mSecond->pos() + QPointF(Point::cRadius, Point::cRadius) ) );
}

void Line::paint(QPainter* painter,
				 const QStyleOptionGraphicsItem* style,
				 QWidget* wgt)
{
	this->setLine( QLineF( mFirst->pos() + QPointF(Point::cRadius, Point::cRadius),
						   mSecond->pos() + QPointF(Point::cRadius, Point::cRadius) ) );

	QLinearGradient gradient( line().p1(), line().p2() );
	gradient.setColorAt(0, Qt::red);
	gradient.setColorAt(1, Qt::blue);

	painter->setBackground(QBrush(gradient));

	QGraphicsLineItem::paint(painter, style, wgt);
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

int Line::type() const
{
	return static_cast<int>(GObjectType::Line);
}
