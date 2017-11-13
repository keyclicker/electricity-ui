#include <Scheme.hpp>

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

#include <Debug.hpp>

std::shared_ptr<VectorXb> Scheme::run()
{
	if (mTester())
		return mSolver(0.0, true );
	else
	{
		Debug() << "Short circuit!\n";
		return nullptr;
	}
}

Scheme::Scheme() :
	mSolver(mGraph),
	mTester(mGraph),
	mGraph()
{

}

Scheme::operator Graph& ()
{
	return mGraph;
}
