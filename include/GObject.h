#ifndef GOBJECT_H
#define GOBJECT_H

#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <Point.hpp>
#include <inputwindow.h>

enum class GObjectType
{
	Point = 135324,
	Line,
	Item
};

class GObject : public QObject,
				public QGraphicsPixmapItem
{     
	Q_OBJECT

	public:
		GObject(const QString&, QGraphicsItem* = nullptr);
		virtual ~GObject() {}
		int type() const override;

	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent*) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
		void keyPressEvent(QKeyEvent*) override;

		void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
		void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
		void hoverMoveEvent(QGraphicsSceneHoverEvent*) override;
		virtual void getInput();

		void setFilename(const QString&);

	private:
		void normalize();

	public slots:
		void moveTo(QPointF point);

	protected:
		Point* mFirst;
		Point* mSecond;
		QGraphicsTextItem* mText;
		InputWindow* mInputWindow;
		static const QString sPrefix;
		static const QString sFormat;
		static const QString sStyle;

	private:
		QPointF mDifference;
		QString cFilename;
};

#endif // GOBJECT_H
