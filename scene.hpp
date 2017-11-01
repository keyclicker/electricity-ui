#ifndef SCENE_HPP
#define SCENE_HPP

#include <QGraphicsScene>

class GridScene : public QGraphicsScene
{
	public:
		template<class... Tn>
		GridScene(Tn... args) :
			QGraphicsScene(args...)
		{ }

	protected:
		void drawBackground(QPainter*, const QRectF&) override;
};
#endif // SCENE_HPP
