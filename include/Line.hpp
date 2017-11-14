#ifndef LINE_HPP_INCLUDED
#define LINE_HPP_INCLUDED

#include <QGraphicsItem>
#include <QGraphicsLineItem>

#include <Point.hpp>

class Line : public QGraphicsLineItem
{
	public:
		Line(QPointF, int);

		void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) final;

		int type() const override;

	protected:
		void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;

	private:
		void normalize();

	private:
		Point* mFirst;
		Point* mSecond;
		const qreal cLineWidth;
		const int cGridSize;
};


#endif // COUNTER_HPP_INCLUDED
