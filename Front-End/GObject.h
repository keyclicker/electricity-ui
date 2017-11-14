#ifndef GOBJECT_H
#define GOBJECT_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QObject>
#include <QCursor>
#include <QColor>
#include <QList>

#include "Canvas.h"
#include "InfoTab.h"
#include "mainwindow.h"

#include <QDebug>

//Клас графічної логіки компонента
class GObject : public QObject, public QGraphicsPixmapItem
{     
Q_OBJECT

private:
	//Зміщення курсора від початку координат елемента при привязці
	QPointF difference = QPointF(250, 250);
	InfoTab *infoTab;

public:
	GObject(QGraphicsItem *parent = nullptr);
	virtual ~GObject() {}

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);	
	void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

public slots:
	void moveTo(QPointF point); //Слот переміщення
};

#endif // GOBJECT_H
