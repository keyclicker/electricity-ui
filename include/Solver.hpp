#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QObject>
#include <QGraphicsScene>
#include <utility>
#include <vector>
#include <map>

#include <GObject.h>
#include <Scheme.hpp>

bool operator<(const QPointF&, const QPointF&);

class Solver : public QObject
{
	Q_OBJECT

	public:
		Solver(QObject* = nullptr);
		void run(QGraphicsScene*);

	private:
		void solve();
		std::size_t findRib(QGraphicsItem*);
		void initialize(QGraphicsScene*);
		bool checkType(const int&, const GObjectType&) const;
		std::pair<QPointF, QPointF>
			make_pair(QGraphicsItem*) const;
		void addRib(std::size_t, std::size_t);

	private:
		std::map< QPointF, std::vector<
			QGraphicsItem*> > mMap;
		std::map< std::pair<QPointF, QPointF>,
			bool > mUsed;
		std::vector<QGraphicsItem*> mRib;
		std::map< QPointF, std::size_t > mPointNum;
		std::vector< std::vector<
			QGraphicsItem*> > mFinalRibs;

		std::size_t mVertixCount;
		Scheme mScheme;
};

#endif
