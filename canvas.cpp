#include <canvas.h>

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QTimeLine>
#include <QWidget>
#include <QDebug>

Canvas::Canvas(QWidget* parent) :
	QGraphicsView(parent),
	mNumScheduledScalings(5)
{

}

void Canvas::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton &&
		event->modifiers() == Qt::ShiftModifier)
	{
		mOriginX = event->localPos().x();
		mOriginY = event->localPos().y();
	}

	QGraphicsView::mousePressEvent(event);
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
	QGraphicsView::mouseReleaseEvent(event);
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() == Qt::LeftButton &&
		event->modifiers() == Qt::ShiftModifier)
	{
		QPointF oldp = mapToScene(mOriginX, mOriginY);
		QPointF newp = mapToScene(event->pos());
		QPointF translation = newp - oldp;

		qDebug() << oldp << " " << newp << "\n";

		setSceneRect(sceneRect().x() - translation.x(),
					 sceneRect().y() - translation.y(),
					 sceneRect().width(), sceneRect().height());

		mOriginX = event->x();
		mOriginY = event->y();
	}

	QGraphicsView::mouseMoveEvent(event);
}

void Canvas::wheelEvent ( QWheelEvent * event )
{
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 10;
	mNumScheduledScalings += numSteps;

	if (mNumScheduledScalings * numSteps < 0)
		mNumScheduledScalings = numSteps;

	QTimeLine *anim = new QTimeLine(350, this);
	anim->setUpdateInterval(5);

	connect(anim, SIGNAL (valueChanged(qreal)),
			this, SLOT (scalingTime(qreal)));

	connect(anim, SIGNAL (finished()),
			this, SLOT (animFinished()));

	anim->start();
}

void Canvas::scalingTime(qreal x)
{
	qreal factor = 1.0 + qreal(mNumScheduledScalings) / 350.0;
	scale(factor, factor);
}

void Canvas::animFinished()
{
	if (mNumScheduledScalings > 0)
		mNumScheduledScalings--;
	else
		mNumScheduledScalings++;
	sender()->~QObject();
}
