#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE TestRib

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <memory>
#include <cmath>

#include <SourceOfElectricity.hpp>
#include <SourceOfCurrent.hpp>
#include <Capacitor.hpp>
#include <Resistor.hpp>
#include <Inductor.hpp>
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

	BOOST_AUTO_TEST_CASE( readFromSTDIN )
	{
		Rib r;
			//we can't read empty rib
			BOOST_CHECK_THROW(std::cin >> r, std::logic_error);

		r.setPoints(5, 3);

		std::cout << "Normal input without unrecognized symbols.\n"
					 "Exmple = {\n\t1\n\tE 5.0 -\n}\n";
			BOOST_CHECK_NO_THROW(std::cin >> r);

		std::cout << "Input with unrecognized symbols when reading SourceOfElectricity.\n"
					 "Exmple = {\n\t1\n\tE 5.0 *\n}\n";
			BOOST_CHECK_THROW(std::cin >> r, std::logic_error);

		std::cout << "Input with unrecognized symbols when reading EObjectType.\n"
					 "Exmple = {\n\t1\n\tF 5.0\n}\n";
			BOOST_CHECK_THROW(std::cin >> r, std::logic_error);
	}

	BOOST_AUTO_TEST_CASE( readFromFile )
	{

	}

BOOST_AUTO_TEST_SUITE_END()
