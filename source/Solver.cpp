#include <boost/type_index.hpp>

#include <solver.hpp>

#include <QPointF>
#include <algorithm>

#include <Line.hpp>
#include <QDebug>

bool operator<(const QPointF& lhs, const QPointF& rhs)
{
	return std::make_tuple(lhs.x(), lhs.y()) <
		   std::make_tuple(rhs.x(), rhs.y());
}

Solver::Solver(QObject* parent) :
	QObject(parent),
	mVertixCount{},
	mPointNum{},
	mScheme(),
	mUsed{},
	mMap{},
	mRib{}
{

}

bool Solver::checkType(const int& intType,
					   const GObjectType& gType) const
{
	return intType == static_cast<int>(gType);
}

void Solver::initialize(QGraphicsScene* scene)
{
	const  auto list = scene->items();
	mVertixCount = 0;

		for (const auto& i : list)
			if (checkType( i->type(), GObjectType::Point))
			{
				mUsed[ make_pair(i) ] = false;
				mMap[ i->scenePos() ].push_back( i );
			}

		for (const auto& i : mMap)
			if (i.second.size() >= 3)
			{
				++mVertixCount;
				mPointNum[ i.first ] = mVertixCount;
			}
			else if (i.second.size() == 1)
				throw std::logic_error("Uncorrect scheme");
}

void Solver::run(QGraphicsScene* scene)
{
	qDebug() << "computing...\n";

	initialize(scene);

		for (const auto& i : mMap)
			if ( i.second.size() >= 3 )
			{
				auto first = mPointNum.at( i.first );

				for (const auto& j : i.second)
					if ( !mUsed.at( make_pair(j) ) )
					{
						auto second = findRib(j);

						qDebug() << "Rib:";

						for (const auto& i : mRib)
						{
							if ( checkType(i->type(), GObjectType::Line) )
								qDebug() << "\tLine";
							else if ( checkType(i->type(), GObjectType::Item) )
								qDebug() << "\tBox";
						}

						addRib(first, second);
						mFinalRibs.emplace_back( std::move(mRib) );
						mRib.clear();
					}
			}

	mMap.clear();
	mUsed.clear();
	mPointNum.clear();
}

std::size_t Solver::findRib(QGraphicsItem* item)
{	
	mRib.push_back( item->parentItem() );
	mUsed.at( make_pair(item) ) = true;

	auto childList = item->parentItem()->childItems();
	auto next = ( item->scenePos() == childList.at(0)->scenePos() )?
		 childList.at(1) : childList.at(0);

	auto res = 0;
	if (mMap.at( next->scenePos() ).size() < 3)
	{
		for ( const auto& i : mMap.at( next->scenePos() ) )
			if (!mUsed.at( make_pair(i) ))
				res = findRib( i );
	}
	else
		res = mPointNum.at( next->scenePos() );

	return res;
}

std::pair<QPointF, QPointF> Solver::make_pair(QGraphicsItem* item) const
{
	auto p1 = item->parentItem()->childItems().at(0);
	auto p2 = item->parentItem()->childItems().at(1);

		auto min = std::min( p1->scenePos(), p2->scenePos() );
		auto max = std::max( p1->scenePos(), p2->scenePos() );

	return std::make_pair(min, max);
}

void Solver::solve()
{

}

void Solver::addRib(std::size_t u, std::size_t v)
{
	std::vector<EObject*> rib;

		for (const auto& i : mRib)
			if ( checkType(i->type(), GObjectType::Item) )
				rib.push_back( dynamic_cast<EObject*>(i) );

	Graph(mScheme).addRib(rib, u, v);
}
