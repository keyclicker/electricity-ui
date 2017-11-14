#ifndef SCHEME_HPP_INCLUDED
#define SCHEME_HPP_INCLUDED

#include <ComputeCycles.hpp>
#include <TestSuite.hpp>
#include <Graph.hpp>
#include <istream>
#include <ostream>

class Scheme
{
    public:
		Scheme();
		std::shared_ptr<VectorXb> run();
		void addRib(const std::vector<EObject*>&, std::size_t, std::size_t);
		void resize(std::size_t);

    private:
        Graph mGraph;
		ComputeCycles mSolver;
		TestSuite mTester;
};


#endif
