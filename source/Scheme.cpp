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

void Scheme::addRib(const std::vector<EObject*>& vec,
					std::size_t u, std::size_t v)
{
	mGraph.addRib(vec, u, v);
}

void Scheme::resize(std::size_t size)
{
	mGraph.resize(size);
}

Scheme::Scheme() :
	mSolver(mGraph),
	mTester(mGraph),
	mGraph()
{

}
