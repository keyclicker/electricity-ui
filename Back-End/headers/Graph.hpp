#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <memory>

#include <Rib.hpp>

class Graph
{
    public:
        Graph();

		void read(std::istream&);

		void write(std::ostream&);


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
