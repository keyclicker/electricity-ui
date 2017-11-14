#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE TestRib

#include <boost/test/unit_test.hpp>
#include <fstream>
#include <memory>

#include <Graph.hpp>
#include <Debug.hpp>

const std::string FILENAME = "TestGraph";
const std::ios_base::openmode OPENMODE =
	std::ios_base::out;

BOOST_AUTO_TEST_SUITE( Test )

	BOOST_AUTO_TEST_CASE( readGraph )
	{
		std::ifstream in(FILENAME + ".in");
		Graph g;

			BOOST_REQUIRE_NO_THROW( g.read(in) );

		in.close();
	}

BOOST_AUTO_TEST_SUITE_END()
