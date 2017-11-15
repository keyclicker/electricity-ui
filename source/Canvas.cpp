#include <canvas.h>

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QTimeLine>
#include <QWidget>
#include <QDebug>
#include <QtMath>

#include <Line.hpp>

Canvas::Canvas(QWidget* parent) :
	QGraphicsView(parent),
	mScaleCount(cScaleCount),
	cScaleFactor(1.005),
	cScaleCount(20),
	mOriginX(0.f),
	mOriginY(0.f),
	mMode(Mode::Editing),
	cGridSize(50),
	mDrag(false)
{

}

void Canvas::drawBackground(QPainter* painter, const QRectF& rect)
{
	const int gridSize = cGridSize;

	painter->setPen( QPen( QColor(71, 100, 144), 3 ) );

		qreal left = int( rect.left() ) -
					 int( rect.left() ) % gridSize;
		qreal top = int( rect.top() ) -
					int( rect.top() ) % gridSize;

	QVarLengthArray<QLineF, 100> lines;

	for (qreal x = left; x < rect.right(); x += gridSize)
		lines.append( QLineF(x, rect.top(), x, rect.bottom()) );

	for (qreal y = top; y < rect.bottom(); y += gridSize)
		lines.append( QLineF(rect.left(), y, rect.right(), y) );

	painter->fillRect( rect, QBrush( QColor(51, 88, 137) ) );
	painter->drawLines( lines.data(), lines.size() );
	update();
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
	/*
	Line* l = new Line(mapToScene(event->pos()), cGridSize);
	scene()->addItem(l);
	mMode = Mode::Editing;
	break;
*/
	if (event->button() == Qt::MiddleButton)
	{
		mOriginX = event->x();
		mOriginY = event->y();
	}

	QGraphicsView::mousePressEvent(event);
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::MidButton)
	{
		QPointF oldp = mapToScene(mOriginX, mOriginY);
		QPointF newp = mapToScene(event->pos());
		QPointF translation = newp - oldp;

		setSceneRect(sceneRect().x() - translation.x(),
					 sceneRect().y() - translation.y(),
					 sceneRect().width(), sceneRect().height());

		mOriginX = event->x();
		mOriginY = event->y();

		this->centerOn(-this->pos());
	}

	emit cursorChangePos(mapToScene(event->pos()));
	QGraphicsView::mouseMoveEvent(event);
}

void Canvas::wheelEvent(QWheelEvent* event)
{
	if (event->delta() > 0)
		centerOn( event->posF() );

	mDir = (event->delta() > 0)? 1 : -1;
	makeZoom();
}

void Canvas::scalingTime(qreal x)
{
	qreal scl = qPow(cScaleFactor, mDir);
	scale( scl, scl );
}

void Canvas::animFinished()
{
	sender()->~QObject();
}


void Canvas::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
		case Qt::Key_Plus:
		{
			mDir = 1;
			makeZoom();
			break;
		}

		case Qt::Key_Minus:
		{
			mDir = -1;
			makeZoom();
			break;
		}

		default:
		{
			QGraphicsView::keyPressEvent(event);
			break;
		}
	}

	update();
}

void Canvas::makeZoom()
{
	QTimeLine *anim = new QTimeLine(350, this);
	anim->setUpdateInterval(5);

	connect(anim, SIGNAL( valueChanged(qreal) ),
			this, SLOT( scalingTime(qreal) ));

	connect(anim, SIGNAL( finished() ),
			this, SLOT( animFinished() ));

	anim->start();
}

bool Canvas::isDrag() const
{
	return mDrag;
}

void Canvas::setDrag(bool value)
{
	mDrag = value;
}
