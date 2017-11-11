#ifndef CANVASTEXTURE_H
#define CANVASTEXTURE_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <iostream>
#include "mainwindow.h"

class Canvas : public QGraphicsPixmapItem
{
public:
    explicit Canvas (QGraphicsItem *parent = 0) : QGraphicsPixmapItem(parent)
    {
        this->setFlag(ItemIsSelectable);
        this->setAcceptHoverEvents(true);
    }

    ~Canvas()
    {

    }

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

};



#endif // CANVASTEXTURE_H
