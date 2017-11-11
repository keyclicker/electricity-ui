#include <Graph.hpp>

Graph::Graph() :
	mVertixCount(0),
	mRibsCount(0)
{

}


void Graph::write(std::ostream& out)
{

}

void Graph::read(std::istream& in)
{
	in >> mVertixCount;

	mGraph.resize(mVertixCount);

	std::size_t u{}, v{};

		while (in >> u && in >> v)
		{
			--u; --v;

			std::shared_ptr<Rib> pRib =
				std::make_shared<Rib>(u, v);

				in >> *pRib;

			std::pair< std::shared_ptr<Rib>,
				std::size_t> pair = std::make_pair(
					std::move(pRib), mRibsCount);
			std::shared_ptr<decltype(pair)> pPair =
				std::make_shared<decltype(pair)>(std::move(pair));

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
}
