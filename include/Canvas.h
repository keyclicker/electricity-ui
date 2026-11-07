#ifndef CANVAS_H
#define CANVAS_H
#include <QGraphicsView>
#include <QWidget>

enum class Mode
{
	LinesDrawing,
	ObjectDrawing,
	Scrolling,
	Editing
};

class Canvas : public QGraphicsView
{
	Q_OBJECT

	public:
		explicit Canvas(QWidget* = nullptr);
		~Canvas() {}

		bool isDrag() const;
		void setDrag(bool);
		const int cGridSize;

	protected:
		void drawBackground(QPainter*, const QRectF&) override;
		void mousePressEvent(QMouseEvent*) override;
		void mouseMoveEvent(QMouseEvent*) override;
		void wheelEvent(QWheelEvent*) override;
		void keyPressEvent(QKeyEvent*) override;

	private slots:
		void scalingTime(qreal x);
		void animFinished();

	private:
		void makeZoom();

	signals:
		void cursorChangePos(QPointF point);

	private:
		qreal mOriginX, mOriginY;
		int mScaleCount;
		const int cScaleCount;
		const qreal cScaleFactor;
		int mDir;
		Mode mMode;
		bool mDrag;
};

#endif // CANVAS_H
