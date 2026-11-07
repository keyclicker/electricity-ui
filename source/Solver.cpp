#include <Solver.hpp>

#include <QPointF>
#include <algorithm>

#include <Line.hpp>
#include <QDebug>

#include <SourceOfElectricity.hpp>
#include <SourceOfCurrent.hpp>

bool operator<(const QPoint& lhs, const QPoint& rhs)
{
	return std::make_tuple( lhs.x(), lhs.y() ) <
		   std::make_tuple( rhs.x(), rhs.y() );
}

Solver::Solver(QObject* parent) :
	QObject(parent),
	mVertixCount{},
	mPointNum{},
	mScheme(),
	mLines{},
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
			if ( checkType( i->type(), GObjectType::Point) )
			{
				mMap[ i->scenePos().toPoint() ].push_back( i );
				mUsed[ make_pair(i) ] = false;
			}

		for (const auto& i : mMap)
			if (i.second.size() >= 3)
			{
				++mVertixCount;
				mPointNum[ i.first ] = mVertixCount;
			}
			else if (i.second.size() == 1)
			{
				clear();
				throw std::logic_error("Uncorrect scheme");
			}
}

void Solver::run(QGraphicsScene* scene)
{
	initialize(scene);

	if (mVertixCount == 0)
	{
		mScheme.resize( 1 );

		auto list = scene->items();

			for (auto& i : list)
				if ( checkType(i->type(), GObjectType::Item) )
					mRib.push_back(i);

		addRib(1, 1);
		mRib.clear();
	}

	else

	{
		mScheme.resize( mVertixCount );

		for (const auto& i : mMap)
			if ( i.second.size() >= 3 )
			{
				auto first = mPointNum.at( i.first );

				for (const auto& j : i.second)
					if ( !mUsed.at( make_pair(j) ) )
					{
						auto second = findRib(j);

						addRib(first, second);

						mRib.clear();
					}
			}

		solve();
	}
}

std::size_t Solver::findRib(QGraphicsItem* item)
{	
	mRib.push_back( item->parentItem() );
	mUsed.at( make_pair(item) ) = true;

	auto parent = item->parentItem();

	if ( checkType(parent->type(), GObjectType::Item) )
	{
		auto eItem = dynamic_cast<EObject*>(parent);

			if (eItem->getType() == EObjectType::SourceOfElectricity)
				static_cast<SourceOfElectricity*>(eItem)->setDirection(
					static_cast<Point*>(item)
				);

			if (eItem->getType() == EObjectType::SourceOfCurrent)
				static_cast<SourceOfCurrent*>(eItem)->setDirection(
					static_cast<Point*>(item)
				);
	}


	auto childList = parent->childItems();
	Point* p[2];
	std::size_t count = 0;


		for (const auto& i : childList)
			if (checkType(i->type(), GObjectType::Point))
			{
				p[count] = dynamic_cast<Point*>(i);
				++count;
			}

	auto next = ( p[0]->scenePos().toPoint() ==
				  item->scenePos().toPoint() )?
		p[1] : p[0];

	if (mMap.at( next->scenePos().toPoint() ).size() < 3)
	{
		for ( const auto& i : mMap.at( next->scenePos().toPoint() ) )
			if (!mUsed.at( make_pair(i) ))
				return findRib( i );
	}
	else
		return mPointNum.at( next->scenePos().toPoint() );
}

std::pair<QPoint, QPoint> Solver::make_pair(QGraphicsItem* item) const
{
	auto childList = item->parentItem()->childItems();
	std::size_t count = 0;
	Point* p[2];

		for (const auto& i : childList)
			if (checkType(i->type(), GObjectType::Point))
			{
				p[count] = dynamic_cast<Point*>(i);
				++count;
			}

	auto min = std::min( p[0]->scenePos().toPoint(), p[1]->scenePos().toPoint() );
	auto max = std::max( p[0]->scenePos().toPoint(), p[1]->scenePos().toPoint() );

	return std::make_pair(min, max);
}

void Solver::solve()
{
	auto res = mScheme.run();

	if (res == nullptr)
		throw std::logic_error("Short circuit");

	for (std::size_t i = 0; i < res->rows(); ++i)
	{
		for (auto& j : mFinalRibs.at(i))
			j->setCurrent( (*res)(i) );

		for (auto& j : mLines.at(i))
			j->setCurrent( QPoint(0, 0) );
	}

}

void Solver::addRib(std::size_t u, std::size_t v)
{
	std::vector<EObject*> eRib;
	std::vector<Line*> gRib;

		for (const auto& i : mRib)
			if ( checkType(i->type(), GObjectType::Item) )
				eRib.push_back( dynamic_cast<EObject*>(i) );
			else if ( checkType(i->type(), GObjectType::Line) )
				gRib.push_back( dynamic_cast<Line*>(i) );

	mScheme.addRib(eRib, u, v);
	mFinalRibs.emplace_back( std::move(eRib) );
	mLines.emplace_back( std::move(gRib) );
}

void Solver::clear()
{
	mMap.clear();
	mUsed.clear();
	mPointNum.clear();
	mFinalRibs.clear();
	mRib.clear();
	mLines.clear();
	mVertixCount = 0;
}

Solver::~Solver()
{
	const cpp_float null("0.0");
	for (const auto& i : mFinalRibs)
		for (auto& j : i)
			j->setCurrent(null);

	for (const auto& i : mLines)
		for (auto& j : i)
			j->setCurrent( QPoint(1, -3) );

	clear();
}
