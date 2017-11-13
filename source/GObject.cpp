#include <GObject.h>
#include <Canvas.h>

#include <QtGlobal>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMoveEvent>
#include <QKeyEvent>

#define VIEW this->scene()->views().first()
#define CANVAS dynamic_cast<Canvas*>(VIEW)

const QString GObject::sPrefix = ":/icons/icons/";
const QString GObject::sFormat = ".png";

GObject::GObject(const QString& file, QGraphicsItem* parent) :
	QGraphicsPixmapItem(parent),
	cFilename(file)
{
	this->setPixmap( QPixmap(sPrefix + cFilename + sFormat) );
	this->setAcceptHoverEvents(true);
	this->setFlags(ItemIsMovable | ItemIsFocusable);

	this->mDifference = QPointF( pixmap().width() / 2,
								 pixmap().height() / 2);
}

void GObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	static auto zVal = this->zValue(); //Костиль

	if(event->button() == Qt::LeftButton)
	{
		CANVAS->setDrag( !CANVAS->isDrag() );

		if (CANVAS->isDrag() && collidingItems().isEmpty())
		{
			connect( CANVAS, SIGNAL( cursorChangePos(QPointF) ),
					this, SLOT( moveTo( QPointF) )
			);

			this->setZValue(1.1);

			this->setPixmap( QPixmap(sPrefix + cFilename +
									 "_drag" + sFormat) );

			mDifference = mapToScene(event->pos()) - this->pos();
		}
		else if ( collidingItems().isEmpty() )
		{
			disconnect( CANVAS, SIGNAL( cursorChangePos(QPointF) ),
						this, SLOT( moveTo(QPointF) )
			);

			this->setZValue(zVal);
			this->setPixmap( QPixmap(sPrefix + cFilename + sFormat) );
			normalize();
		}
	}

	if (CANVAS->isDrag() && event->button() == Qt::RightButton)
    {
		this->setTransformOriginPoint( QPointF(
			this->pixmap().width() / 2,
			this->pixmap().height() / 2 )
		);

		this->setRotation( this->rotation() + 90 );

		mDifference = QPoint( pixmap().width() / 2,
							  pixmap().height() / 2);

		QCursor::setPos(
						VIEW->mapToGlobal(
						VIEW->mapFromScene( pos() + QPoint(pixmap().width() / 2,
														   pixmap().height() / 2) )
					)
		);
    }

    static InputWindow *win;
    if (!CANVAS->isDrag() && event->button() == Qt::RightButton)
    {
        win = new InputWindow("I:","Volt");
    }
}

void GObject::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Delete)
    {
		CANVAS->setDrag(false);
		this->scene()->removeItem(this);
	}
}

void GObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{

}

void GObject::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

}


void GObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{

}

void GObject::moveTo(QPointF point)
{
	this->setVisible(true);

	if( !collidingItems().isEmpty() )
		this->setPixmap( QPixmap(sPrefix + cFilename + "_collision" + sFormat) );
    else
		this->setPixmap( QPixmap(sPrefix + cFilename + "_drag" + sFormat) );

	this->setPos(point - mDifference);
}

int GObject::type() const
{
	return static_cast<int>(GObjectType::Item);
}

void GObject::normalize()
{
	const float step = 50;

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

#undef VIEW
#undef CANVAS
