#ifndef BOX_HPP
#define BOX_HPP

#include <QGraphicsItem>
#include <QColor>
#include <QPoint>

class Box : public QGraphicsItem
{
	public:
		Box(const QString&);

		QRectF boundingRect() const override;
		QPainterPath shape() const override;
		void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

	protected:
		void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
		void mousePressEvent(QGraphicsSceneMouseEvent*) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;

	private:
		QPixmap mImage;
};

#endif // BOX_HPP
