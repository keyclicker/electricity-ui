#include "GObject.h"
#define VIEW this->scene()->views().first()
#define CANVAS dynamic_cast<Canvas*>(VIEW)

extern MainWindow *mainWindow;

GObject::GObject(QGraphicsItem *parent) :
	QGraphicsPixmapItem(parent)
{
    this->setAcceptHoverEvents(true);
	this->setFlags(ItemIsMovable | ItemIsFocusable);

	this->setPixmap(QPixmap(":/resources/icons/Resistor.png"));
}

//Прив'язуєм обєкт до курсора
void GObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	static auto zval = this->zValue(); //Костиль

    if(event->button() == Qt::LeftButton)
    {
		CANVAS->setDrag(!CANVAS->isDrag());
		if (CANVAS->isDrag() && collidingItems().isEmpty())
        {
			infoTab->setVisible(false);

			//Тут і іде прив'зка
			connect(CANVAS, SIGNAL(cursorChangePos(QPointF)),
					 this, SLOT(moveTo(QPointF)));

			//Костиль
			this->setZValue(0.1);

			//Тимчасово,текстури будуть статично загружатись в фінальних класах
	//		this->setPixmap(QPixmap(":/resources/icons/Resistor_drag.png"));

			//Записуємо різницю
			difference = mapToScene(event->pos()) - this->pos();
        }
        else if (collidingItems().isEmpty())
        {
			infoTab->setVisible(true);

			//Відповідно відв'язка
			disconnect(CANVAS, SIGNAL(cursorChangePos(QPointF)),
					   this, SLOT(moveTo(QPointF)));

            this->setZValue(zval); //Костиль
	//		this->setPixmap(QPixmap(":/resources/icons/Resistor.png"));
        }
   }

	if (CANVAS->isDrag() && event->button() == Qt::RightButton) //Обертаєм елемент
    {
		this->setTransformOriginPoint
			(QPointF(this->pixmap().width() / 2, this->pixmap().height() / 2));

        this->setRotation(this->rotation() + 90);

		//Ставимо різницю в центр, ібо без цього буде болюче
		difference = QPoint(250, 250);

		//Собствєнно переміщаєм його в центр
		QCursor::setPos(VIEW->mapToGlobal
				(VIEW->mapFromScene(pos() + QPoint(250, 250))));
    }
}

void GObject::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Delete)
    {
		CANVAS->setDrag(false);
		delete this->infoTab;
		this->scene()->removeItem(this);
	}
}

void GObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	if (!CANVAS->isDrag())
	{
		infoTab->setVisible(true);
		infoTab->move(mainWindow->mapFromGlobal(QCursor::pos() + QPoint(-infoTab->width(), 1)));
	}
}

void GObject::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	infoTab->move(mainWindow->mapFromGlobal(QCursor::pos() + QPoint(-infoTab->width(), 1)));
}


void GObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	infoTab->setVisible(false);
}

void GObject::moveTo(QPointF point)
{
	this->setVisible(true); //Очередний костиль

	 //Че'каєм чи ця хрєнь не пересікається
	if(!collidingItems().isEmpty())
    {
        this->setPixmap(QPixmap(":/resources/icons/Resistor_collision.png"));
    }
    else
    {
        this->setPixmap(QPixmap(":/resources/icons/Resistor_drag.png"));
    }

    this->setPos(point - difference);
}

#undef VIEW
#undef CANVAS
