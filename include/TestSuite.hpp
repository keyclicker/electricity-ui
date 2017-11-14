#ifndef TESTSUITE_HPP_INCLUDED
#define TESTSUITE_HPP_INCLUDED

#include <cstdint>
#include <vector>

#include <Graph.hpp>
#include <static.hpp>

class TestSuite
{
	public:
		TestSuite(Graph&);
		bool operator()();

	private:
		bool dfs(std::size_t, std::size_t, std::size_t);
		void precompute();
		bool computeCycles();
		bool equalNull(const cpp_float&) const;

	private:
		std::vector<char> mUsed;
		std::vector<char> mUsedVert;
		std::vector<char> mValues;
		Graph& mG;
};

#endif
