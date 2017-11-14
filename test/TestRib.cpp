#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE TestRib

#include <boost/test/unit_test.hpp>
#include <fstream>
#include <vector>
#include <memory>

#include <Rib.hpp>

BOOST_AUTO_TEST_SUITE( Test )

	BOOST_AUTO_TEST_CASE( checkCoutPoints )
	{
		std::size_t u = 5,
					v = 6;
		Rib r(--u, --v);

			BOOST_TEST_REQUIRE(r.getAnother(u) == v);
			BOOST_TEST_REQUIRE(r.getAnother(v) == u);

			BOOST_CHECK_THROW(r.getAnother(0), std::logic_error);
			BOOST_CHECK_NO_THROW(r.getAnother(u));
			BOOST_CHECK_NO_THROW(r.getAnother(v));

		u = 72;
		v = 8;

		BOOST_CHECK_THROW(r.setPoints(320, 0), std::logic_error);
		BOOST_CHECK_NO_THROW(r.setPoints(u, v););

			BOOST_TEST_REQUIRE(r.getAnother(u) == v);
			BOOST_TEST_REQUIRE(r.getAnother(v) == u);
			BOOST_CHECK_NO_THROW(r.getAnother(u));
			BOOST_CHECK_NO_THROW(r.getAnother(v));
	}

	BOOST_AUTO_TEST_CASE( getValue )
	{
		Rib r;

			BOOST_CHECK_THROW(r.getResistance(), std::logic_error);
			BOOST_CHECK_THROW(r.getVoltage(0), std::logic_error);
			BOOST_CHECK_THROW(r.getCurrent(), std::logic_error);

		std::size_t u = 2,
					v = 5;

		r.setPoints(u, v);

			BOOST_CHECK_NO_THROW(r.getResistance());
			BOOST_CHECK_NO_THROW(r.getCurrent());

			BOOST_CHECK_NO_THROW(r.getVoltage(2));

			BOOST_CHECK_THROW(r.getVoltage(1), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE( readFromFileAndCheckValue )
	{
		std::ifstream in("TestRib.in");
		Rib r;

		const std::size_t u = 1;
		const std::size_t v = 2;
		r.setPoints(u, v);
		in >> r;

			BOOST_CHECK_EQUAL( r.getResistance(), cpp_float("10000005.00001") );

		in >> r;

			BOOST_CHECK_EQUAL(r.getUsed(), false);

		in >> r;

			BOOST_CHECK_EQUAL( r.getVoltage(u), cpp_float("0.00000001") );
			BOOST_CHECK_EQUAL( r.getVoltage(v), cpp_float("-0.00000001") );
			BOOST_REQUIRE( !r.getUsed() );

		in.close();
	}

BOOST_AUTO_TEST_SUITE_END()
