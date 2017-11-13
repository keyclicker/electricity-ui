#ifndef COMPUTECYCLES_HPP_INCLUDED
#define COMPUTECYCLES_HPP_INCLUDED

#include <cstdint>
#include <vector>

#include <Graph.hpp>

#include <static.hpp>

class ComputeCycles
{
	public:
		ComputeCycles(Graph&);
		std::shared_ptr<VectorXb> operator()(const double, bool = false);

	private:
		bool dfs(std::size_t, std::size_t, std::size_t);
		void addOtherEqutions();
		void addEquation(std::size_t);
		void computeCycles();
		void normalize();
		void create();
		void clear();

	private:
		std::shared_ptr<VectorXb> mSolution;
		const cpp_float cEpsilon;

		std::vector<char> mUsedVert;
		std::vector<char> mUsed;//for dfs
		VectorXb mFreeCoef;
		MatrixXb mMatrix;

		std::vector<Graph::PairPointer>
				mPath;

		std::size_t mEquantionsCount;
		Graph& mG;
};




#endif
