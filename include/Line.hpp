#ifndef LINE_HPP_INCLUDED
#define LINE_HPP_INCLUDED

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QObject>

#include <Point.hpp>
#include <QPointF>

class Line : public QObject,
			 public QGraphicsLineItem
{
	Q_OBJECT
	public:
		Line(QPointF, int);
		Line(QPoint, QPoint);

		void setCurrent(QPoint);

		void updateLine();
		void startDrawing();
		void pointReleased();
		int type() const override;

	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent*) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
		void keyPressEvent(QKeyEvent*) override;

	private:
		void normalize();
		void remove();

	public slots:
		void moveTo(QPointF point);

	private:
		Point* mFirst;
		Point* mSecond;
		const qreal cLineWidth;
		const int cGridSize;
		QPointF mDifference;

	private slots:
		void movePoint(QPointF point);
};


#endif // COUNTER_HPP_INCLUDED
