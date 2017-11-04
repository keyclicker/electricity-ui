#include <TestSuite.hpp>
#include <iostream>
#include <iomanip>

bool TestSuite::equalNull(const cpp_float& val) const
{
	static const cpp_float null = cpp_float("0.0");
	return val == null;
}

TestSuite::TestSuite(Graph& g) :
	mG(g),
	mValues()
{

};

bool TestSuite::operator()()
{
	auto res = computeCycles();
	precompute();
	return res;
}

void TestSuite::precompute()
{
	for (const auto& i : mG.mGraph)
		for (const auto& j : i)
			for (const auto& k :  j->first->mElements)
				if ( ( k->getType() == EObjectType::Capacitor ||
					   k->getType() == EObjectType::Switch ) &&
					  !j->first->getUsed() )
				{
					j->first->setUsed(true);
				}
}

bool TestSuite::computeCycles()
{
	mValues.resize(mG.mRibsCount);
	mUsed.assign(mG.mRibsCount, false);

	for (const auto& i : mG.mGraph)
		for (const auto& j : i)
			mValues.at(j->second) =
				equalNull(j->first->getResistance());


	for (std::size_t i = 0; i < mG.mVertixCount; ++i)
		for(const auto& j : mG.mGraph.at(i))
			if( !mUsed.at(j->second) &&
				mValues.at(j->second) &&
				( j->first->getVoltage(i).compare(0) != 0 ||
				  j->first->getCurrent().compare(0) != 0 )
			  )
			{
				mUsed.at(j->second) = true;
				mUsedVert.assign(mG.mVertixCount, false);

					if (dfs( j->first->getAnother(i), i, j->second ))
						return false;

				mUsedVert.clear();
			}

	mValues.clear();
	mUsed.clear();

	return true;
}

bool TestSuite::dfs(std::size_t u,
					std::size_t end,
					std::size_t usedRib)
{
	mUsedVert.at(u) = true;

		for (const auto& i : mG.mGraph.at(u))
		{
			auto to = i->first->getAnother(u);

				if( i->second == usedRib || !mValues.at(i->second) )
					continue;

				if (to == end)
				{
					mUsed.at(i->second) = true;
					return true;
				}

				if (!mUsedVert.at(to) &&
					dfs(to, end, usedRib))
				{
					mUsed.at(i->second) = true;
					return true;
				}
		}

	return false;
}
