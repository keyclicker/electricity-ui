#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <utility>
#include <vector>
#include <memory>

#include <Rib.hpp>

class Graph
{
    public:
        Graph();

		void resize(std::size_t);

		void addRib(const std::vector<EObject*>&,
					std::size_t u, std::size_t v);

    private:

		using PairPointer = std::shared_ptr< std::pair<
			std::shared_ptr<Rib>, std::size_t > >;

		std::vector< std::vector< PairPointer > >
				mGraph;
        std::size_t mVertixCount;
		std::size_t mRibsCount;

		friend class ComputeCycles;
		friend class TestSuite;
};

#endif
