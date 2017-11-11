#include <TestSuite.hpp>
#include <iostream>
#include <iomanip>

#include <Debug.hpp>

bool TestSuite::equalNull(const cpp_float& val) const
{
	static const cpp_float null = cpp_float("0.0");
	return val == null;
}

TestSuite::TestSuite(Graph& g) :
	mG(g),
	mValues()
{
	Debug() << " -> TestSuite created.\n";
}

bool TestSuite::operator()()
{
	auto res = computeCycles();
	precompute();

		Debug() << " -> TestSuite::computing\n";

		Debug()
				<< "\nHas short circuit: "
				<< std::boolalpha
				<< !res
				<< "\n";

	return res;
}

void TestSuite::precompute()
{

}

bool TestSuite::computeCycles()
{
	mValues.resize(mG.mRibsCount);
	mUsed.assign(mG.mRibsCount, false);

	for (const auto& i : mG.mGraph)
		for (const auto& j : i)
			mValues.at(j->second) =
				equalNull(j->first->getResistance());

		Debug() << "mValues = { ";

			for (const auto& i : mValues)
				Debug() << (i? 1 : 0) << " ";

		Debug() << "}\n";


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
					{
						Debug()
								<< j->first->getAnother(i)
								<< " }\n";

						return false;
					}

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

						Debug()
								<< "DFS = { "
								<< to << " ";

					return true;
				}

				if (!mUsedVert.at(to) &&
					dfs(to, end, usedRib))
				{
					mUsed.at(i->second) = true;

						Debug()
								<< to << " ";

					return true;
				}
		}

	return false;
}
