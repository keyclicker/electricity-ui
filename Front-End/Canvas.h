#ifndef CANVAS_H
#define CANVAS_H
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMetaMethod>
#include <QWidget>
#include <cmath>


class Canvas : public QGraphicsView
{
 Q_OBJECT

private:
	double originX, originY;
	int scaleFactor = 5;
	bool Drag; //Чи переміщається якийч айтем на канваві

public:
	explicit Canvas(QWidget* = nullptr);
    ~Canvas() {}

	bool isDrag() const;
	void setDrag(bool value);

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;

	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

signals:
    void cursorChangePos(QPointF point);

public slots:
    void scalingTime(qreal x);
    void animFinished();
};

#endif // CANVAS_H
