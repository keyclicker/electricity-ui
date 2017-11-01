#include <box.hpp>
#include <QtWidgets>
#include <QtGlobal>

Box::Box(const QString& filename)
{
	setFlags(ItemIsSelectable | ItemIsMovable);
	setAcceptHoverEvents(true);

	if (!mImage.load(filename))
		qDebug() << "Can't load!\n";
}

QRectF Box::boundingRect() const
{
	return QRectF(0, 0, mImage.width(),
						mImage.height());
}

QPainterPath Box::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

void Box::paint(QPainter* painter,
				const QStyleOptionGraphicsItem* item,
				QWidget* widget)
{
	painter->drawPixmap(mImage.rect(), mImage);
}

void Box::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mousePressEvent(event);
}

void Box::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
}

void Box::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

	qDebug() << event->scenePos() << "\n";

	QGraphicsItem::mouseMoveEvent(event);
}
