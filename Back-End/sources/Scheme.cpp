#include <Scheme.hpp>

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

#include <Debug.hpp>
#include <debug/vector>

void Scheme::run(std::ostream& out)
{
	/*
    using namespace std::chrono;

	const auto timePerStep = 0.1s;
    const auto dTimePerStep = 0.1d;// we pass it as argument to compute current
                                   // cause there're a lot of work with std::chrono::duration
	const auto runTime = 0.5s;
	auto countOfTime = 0.0s;
	std::size_t countOfSteps{0};
	*/

	if (mTester())
		out
			<< std::fixed
			<< std::setprecision(std::numeric_limits<cpp_float>::digits10)
			<< *mSolver( /*dTimePerStep * countOfSteps*/ 0.0, true );
	else
		Debug() << "Short circuit!\n";

	/*
	if (mTester())
	{

		while(countOfTime <= runTime)
		{
			auto begin = steady_clock::now();

				auto res = mSolver(dTimePerStep * countOfSteps);
				++countOfSteps;

			auto end = steady_clock::now();

			auto dt = duration_cast<seconds>(end - begin);

			std::this_thread::sleep_until(begin + dt + timePerStep);

			countOfTime += timePerStep;

				//--------------------will be removed
					cout << "//----------------// " << (dTimePerStep) * (countOfSteps - 1)
						 << "s //-----------------------//\n";
					cout
						<< std::fixed
						<< std::setprecision(std::numeric_limits<cpp_float>::digits10)
						<< *res << "\n";
		}
	}
	*/
}

Scheme::Scheme(std::istream& in) :
	mSolver(mGraph),
	mTester(mGraph),
	mGraph()
{
	mGraph.read(in);
}
