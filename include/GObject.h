#ifndef GOBJECT_H
#define GOBJECT_H

#include <QGraphicsPixmapItem>
#include <Point.hpp>

#include "InputWindow.h"

enum class GObjectType
{
	Point,
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
		void keyPressEvent(QKeyEvent*) override;

		void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
		void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
		void hoverMoveEvent(QGraphicsSceneHoverEvent*) override;

	private:
		void normalize();

	public slots:
		void moveTo(QPointF point);

	private:
		QPointF mDifference;

		const QString cFilename;
		static const QString sPrefix;
		static const QString sFormat;
};

#endif // GOBJECT_H
