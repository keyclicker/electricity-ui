#include <Graph.hpp>

Graph::Graph() :
	mVertixCount(0),
	mRibsCount(0)
{

}

void Graph::resize(std::size_t size)
{
	mRibsCount = 0;
	mVertixCount = size;
	mGraph.resize(mVertixCount);
}

void Graph::addRib(const std::vector<EObject*>& vec,
				   std::size_t u, std::size_t v)
{
	--u; --v;

	std::shared_ptr<Rib> pRib =
		std::make_shared<Rib>(u, v);

		for (const auto& i : vec)
			pRib->addElement( i );

	std::pair< std::shared_ptr<Rib>,
		std::size_t> pair = std::make_pair(
			std::move(pRib), mRibsCount);

	std::shared_ptr<decltype(pair)> pPair =
		std::make_shared<decltype(pair)>( std::move(pair) );

	try
	{
		mGraph.at(u).emplace_back(pPair);
		mGraph.at(v).emplace_back(pPair);
	}
	catch(std::out_of_range& e)
	{

	}

	++mRibsCount;
}

