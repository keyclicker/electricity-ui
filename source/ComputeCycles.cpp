#include <ComputeCycles.hpp>

#include <iomanip>
#include <Debug.hpp>

ComputeCycles::ComputeCycles(Graph& G) :
	mEquantionsCount(0),
	cEpsilon(pow(cpp_float("10"), -16.0)),
	mG(G)
{
	mSolution = std::make_shared<VectorXb>();

	Debug() << " -> ComputeCycles created.\n";
}

std::shared_ptr<VectorXb> ComputeCycles::operator()(const double dt, bool flag)
{
	if (!flag)
		return mSolution;

	Debug() << " -> ComputeCycles::computing\n";

	try
	{
		create();

		if (mG.mRibsCount == 1)
		{
			mSolution->resize(1);
			if ( !mG.mGraph.front().front()->first->getUsed() )
				(*mSolution)(0) = 0;
			else
				(*mSolution)(0) = mG.mGraph.front().front()->first->getVoltage(0) /
								  mG.mGraph.front().front()->first->getResistance();
			return mSolution;
		}

		computeCycles();
		addOtherEqutions();
		normalize();

		*mSolution = mMatrix.colPivHouseholderQr().solve(mFreeCoef);

		 Debug() << "Matrix after computing:\n"
				  << mMatrix << "\n"
				  << "FreeCoef after computing:\n"
				  << mFreeCoef << "\n"
				  << "Vector of solution after solving:\n"
				  << std::fixed
				  << std::setprecision(std::numeric_limits<cpp_float>::digits10)
				  << *mSolution << "\n";

		clear();
	}
	catch(std::logic_error& e)
	{
		throw;
	}

	return mSolution;
}

bool ComputeCycles::dfs(std::size_t u,
						std::size_t end,
						std::size_t usedRib)
{
	mUsedVert.at(u) = true;

		for (const auto& i : mG.mGraph.at(u))
		{
			auto to = i->first->getAnother(u);

				if(i->second == usedRib || !i->first->getUsed())
					continue;

				if (to == end)
				{
					mPath.emplace_back(i);
					mUsed.at(i->second) = true;
					return true;
				}

				if (!mUsedVert.at(to) && dfs(to, end, usedRib))
				{
					mPath.emplace_back(i);
					mUsed.at(i->second) = true;
					return true;
				}
		}

	return false;
}

void ComputeCycles::create()
{
	mMatrix.resize(mG.mRibsCount, mG.mRibsCount);
	mFreeCoef.resize(mG.mRibsCount);
	mUsed.assign(mG.mRibsCount, false);

		for (int i = 0; i < mMatrix.cols(); ++i)
		{
			mFreeCoef(i) = 0.0;

			for (int j = 0; j < mMatrix.rows(); ++j)
				mMatrix(i, j) = 0.0;
		}

		for (const auto& i : mG.mGraph)
			for(const auto& j : i)
				if ( j->first->getCurrent() != 0 &&
					 !mUsed.at(j->second) &&
					 j->first->getUsed() )
				{
					mUsed.at(j->second) = true;
					mFreeCoef(mEquantionsCount) = j->first->getCurrent();
					mMatrix(mEquantionsCount, j->second) = 1.0;
					++mEquantionsCount;
				}

		for(const auto& i : mG.mGraph)
			for (const auto& j : i)
				if ( !j->first->getUsed() && !mUsed.at(j->second) )
				{
					mUsed.at(j->second) = true;
					mFreeCoef(mEquantionsCount) = 0.0;
					mMatrix(mEquantionsCount, j->second) = 1.0;
					++mEquantionsCount;
				}

		Debug()   << "Matrix after initialithing:\n"
				  << mMatrix << "\n"
				  << "FreeCoef after initializing:\n"
				  << mFreeCoef << "\n"
				  << "Vector of solution after initialithing:\n"
				  << *mSolution << "\n";
}

void ComputeCycles::clear()
{
	mFreeCoef.resize(0);
	mMatrix.resize(0, 0);
	mUsed.clear();
	mEquantionsCount = 0;
}

void ComputeCycles::computeCycles()
{
	for (std::size_t i = 0; i < mG.mVertixCount; ++i)
		for(const auto& j : mG.mGraph.at(i))
			if(!mUsed.at(j->second))
			{
				mUsed.at(j->second) = true;
				mUsedVert.assign(mG.mVertixCount, false);

					if (dfs(j->first->getAnother(i), i, j->second))
					{
						mPath.emplace_back(j);
						addEquation(i);
					}

				mUsedVert.clear();
				mPath.clear();
			}
}

void ComputeCycles::addEquation(std::size_t point)
{
	int j = point;

	Debug() << "\nDFS = {\n";

		for (const auto& i : mPath)
		{
			Debug()  << "    {" << j + 1 << ", " << i->first->getAnother(j) + 1
					  << "} = [" << i->second + 1 << "]\n";

			j = i->first->getAnother(j);
		}

	Debug() << "}\n";

	for (const auto& i : mPath)
	{
		point = i->first->getAnother(point);
		mFreeCoef(mEquantionsCount) += i->first->getVoltage(point);
		mMatrix(mEquantionsCount, i->second) = i->first->defCurrDirection(point) *
											   i->first->getResistance();
	}

	++mEquantionsCount;
}

void ComputeCycles::addOtherEqutions()
{
	Debug()
			<< "Inside ComputeCycles::addOtherEquations()\n"
			<< mEquantionsCount << " "
			<< mG.mVertixCount << " "
			<< mG.mRibsCount << "\n";

	if (mG.mVertixCount - 1 != mG.mRibsCount - mEquantionsCount)
		throw std::logic_error("ComputeCycles::addOtherEquations(): "
							   "some problem has occured when finding cycles.");

	for (std::size_t i = 0; i < mG.mVertixCount - 1; ++i)
	{
		for (std::size_t j = 0; j < mG.mGraph.at(i).size(); ++j)
			mMatrix(mEquantionsCount, mG.mGraph.at(i).at(j)->second) =
				mG.mGraph.at(i).at(j)->first->defCurrDirection(i);
		++mEquantionsCount;
	}
}

void ComputeCycles::normalize()
{
	for (int i = 0; i < mSolution->rows(); ++i)
		if( cEpsilon.compare(boost::multiprecision::fabs( (*mSolution)(i) )) >= 0 )
			(*mSolution)(i) = 0.0;
}
