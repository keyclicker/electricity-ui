#include "Canvas.h"
#include <QMouseEvent>
#include <QTimeLine>
#include <QGraphicsView>
#include <QWidget>
#include <QDebug>


bool Canvas::isDrag() const
{
	return Drag;
}

void Canvas::setDrag(bool value)
{
	Drag = value;
}

Canvas::Canvas(QWidget* parent) : QGraphicsView(parent)
{
	this->setRenderHints(QPainter::Antialiasing);

	this->setMouseTracking(true);
}

void Canvas::drawBackground(QPainter* painter, const QRectF& rect)
{
	const int gridSize = 110;
	painter->setBackground( QBrush( QColor(51, 88, 137) ) );
	painter->setPen( QPen( QColor(71, 100, 144), 8) );

	qreal left = int( rect.left() ) - (int( rect.left() ) % gridSize);
	qreal top = int(rect.top()) - (int(rect.top()) % gridSize);

	QVarLengthArray<QLineF, 100> lines;

	for (qreal x = left; x < rect.right(); x += gridSize)
		lines.append(QLineF(x, rect.top(), x, rect.bottom()));
	for (qreal y = top; y < rect.bottom(); y += gridSize)
		lines.append(QLineF(rect.left(), y, rect.right(), y));

	painter->fillRect( rect, QBrush( QColor(51, 88, 137) ) );
	painter->drawLines(lines.data(), lines.size());
}


void Canvas::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton)
    {
        originX = event->x();
        originY = event->y();
    }

    QGraphicsView::mousePressEvent(event);
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::MidButton)
    {
        QPointF oldp = mapToScene(originX, originY);
        QPointF newp = mapToScene(event->pos());
        QPointF translation = newp - oldp;

        setSceneRect(sceneRect().x() - translation.x(),
                     sceneRect().y() - translation.y(),
                     sceneRect().width(), sceneRect().height());

        originX = event->x();
        originY = event->y();

		this->centerOn(-this->pos());
    }

    emit cursorChangePos(mapToScene(event->pos()));
    QGraphicsView::mouseMoveEvent(event);
}

void Canvas::wheelEvent ( QWheelEvent * event )
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 10; // see QWheelEvent documentation

	if (numSteps > 0) scaleFactor = abs(scaleFactor);
	else scaleFactor = -abs(scaleFactor);

    QTimeLine *anim = new QTimeLine(350, this);
	anim->setUpdateInterval(5);

	connect(anim,SIGNAL (valueChanged(qreal)), this,SLOT (scalingTime(qreal)));
	connect(anim,SIGNAL (finished()), this,SLOT (animFinished()));
    anim->start();
}

void Canvas::scalingTime(qreal x)
{
	qreal factor = 1.0+ qreal(scaleFactor) / 300.0;

	scale(factor, factor);
}

void Canvas::animFinished()
{
	sender()->~QObject();
}

