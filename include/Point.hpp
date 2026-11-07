#ifndef CONNECTOR_HPP_INCLUDED
#define CONNECTOR_HPP_INCLUDED

#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPoint>

class Point : public QGraphicsItem
{
	public:
		Point(int, QGraphicsItem* = nullptr);

		int type() const override;
		QRectF boundingRect() const override;
		QPainterPath shape() const override;
		void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

		void normalize();

		Point(const Point&) = delete;
		Point& operator=(const Point&) = delete;

	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
		QVariant itemChange(GraphicsItemChange, const QVariant&) override;
		void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
		void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

	public:
		static const qreal cRadius;

	private:
		const int cGridSize;
		QPen mDefPen;
		QPen mHoverPen;
		QBrush mDefBrush;
		QBrush mHoverBrush;
		bool mHover;
};

#endif // COUNTER_HPP_INCLUDED
