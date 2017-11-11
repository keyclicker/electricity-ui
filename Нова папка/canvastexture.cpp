#include "canvastexture.h"
#include <QGraphicsView>

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	this->scene()->views()[0]->setSceneRect
			(
				-this->scene()->views()[0]->mapToScene(event->pos().x(),
													   event->pos().y()).x()/2,

				-this->scene()->views()[0]->mapToScene(event->pos().x(),
													   event->pos().y()).y()/2,
				1, 1
			);
}
