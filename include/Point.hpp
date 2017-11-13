#ifndef CONNECTOR_HPP_INCLUDED
#define CONNECTOR_HPP_INCLUDED

#include <QGraphicsItem>
#include <QBrush>
#include <QPen>

class Point : public QGraphicsItem
{
	public:
		Point(qreal, int, QGraphicsItem* = nullptr);

		int type() const override;
		QRectF boundingRect() const override;
		QPainterPath shape() const override;
		void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

		void normalize();

		Point(const Point&) = delete;
		Point& operator=(const Point&) = delete;

	protected:
		void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
		void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
		void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

	private:
		const qreal cRadius;
		const int cGridSize;
		QPen mDefPen;
		QPen mHoverPen;
		QBrush mHoverBrush;
		bool mHover;
};

#endif // COUNTER_HPP_INCLUDED
