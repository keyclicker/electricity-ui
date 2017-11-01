#ifndef CANVAS_H
#define CANVAS_H
#include <QGraphicsView>
#include <QWidget>


class Canvas : public QGraphicsView
{
	Q_OBJECT

	public:
		explicit Canvas(QWidget* = nullptr);
		~Canvas() {}

	protected:
		void mousePressEvent(QMouseEvent*);
		void mouseReleaseEvent(QMouseEvent*);
		void mouseMoveEvent(QMouseEvent*);
		void wheelEvent(QWheelEvent*);

	private slots:
		void scalingTime(qreal x);
		void animFinished();

	private:
		float mOriginX, mOriginY;
		int mNumScheduledScalings;
};

#endif // CANVAS_H
