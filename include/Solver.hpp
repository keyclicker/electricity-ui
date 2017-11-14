#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QObject>
#include <QGraphicsScene>
#include <utility>
#include <vector>
#include <map>

#include <GObject.h>
#include <Scheme.hpp>
#include <Line.hpp>

bool operator<(const QPoint&, const QPoint&);

class Solver : public QObject
{
	Q_OBJECT

	public:
		Solver(QObject* = nullptr);
		~Solver();
		void run(QGraphicsScene*);

	private:
		void solve();
		void clear();
		std::size_t findRib(QGraphicsItem*);
		void initialize(QGraphicsScene*);
		bool checkType(const int&, const GObjectType&) const;
		std::pair<QPoint, QPoint>
			make_pair(QGraphicsItem*) const;
		void addRib(std::size_t, std::size_t);

	private:
		std::map< QPoint, std::vector<
			QGraphicsItem*> > mMap;
		std::map< std::pair<QPoint, QPoint>,
			bool > mUsed;
		std::vector<QGraphicsItem*> mRib;
		std::map< QPoint, std::size_t > mPointNum;
		std::vector< std::vector<
			EObject*> > mFinalRibs;
		std::vector< std::vector<
			Line*> > mLines;

		std::size_t mVertixCount;
		Scheme mScheme;
};

#endif
