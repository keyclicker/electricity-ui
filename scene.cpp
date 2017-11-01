#include <scene.hpp>
#include <QPainter>
#include <QDebug>

void GridScene::drawBackground(QPainter* painter, const QRectF& rect)
{
	const int gridSize = 25;
	painter->setBackground( QBrush( QColor(51, 88, 137) ) );
	painter->setPen( QPen( QColor(71, 100, 144), 2 ) );

	qreal left = int( rect.left() ) - (int( rect.left() ) % gridSize);
	qreal top = int(rect.top()) - (int(rect.top()) % gridSize);

	QVarLengthArray<QLineF, 100> lines;

	for (qreal x = left; x < rect.right(); x += gridSize)
		lines.append(QLineF(x, rect.top(), x, rect.bottom()));
	for (qreal y = top; y < rect.bottom(); y += gridSize)
		lines.append(QLineF(rect.left(), y, rect.right(), y));

	qDebug() << lines.size();

	painter->fillRect( rect, QBrush( QColor(51, 88, 137) ) );
	painter->drawLines(lines.data(), lines.size());
}
