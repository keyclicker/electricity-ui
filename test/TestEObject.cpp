/*
 * pass --log_level=test_suite as argument to show detailed description
*/

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE AllDerivedFromEObject

#include <boost/test/unit_test.hpp>
#include <vector>
#include <memory>
#include <cstdlib>
#include <cmath>

#include <SourceOfElectricity.hpp>
#include <SourceOfCurrent.hpp>
#include <Capacitor.hpp>
#include <Resistor.hpp>
#include <Inductor.hpp>
#include <Switcher.hpp>

BOOST_AUTO_TEST_SUITE( Test )

	BOOST_AUTO_TEST_CASE( checkType )
	{
		std::vector<std::unique_ptr<EObject>> vec;

		const std::string someVal = "3.1415927";

			vec.emplace_back(std::make_unique<SourceOfElectricity>(someVal));
			vec.emplace_back(std::make_unique<SourceOfCurrent>(someVal));
			vec.emplace_back(std::make_unique<Capacitor>(someVal));
			vec.emplace_back(std::make_unique<Resistor>(someVal));
			vec.emplace_back(std::make_unique<Inductor>(someVal));
			vec.emplace_back(std::make_unique<Switch>(true));

		BOOST_CHECK(vec.at(0)->getType() == EObjectType::SourceOfElectricity);
		BOOST_CHECK(vec.at(1)->getType() == EObjectType::SourceOfCurrent);
		BOOST_CHECK(vec.at(2)->getType() == EObjectType::Capacitor);
		BOOST_CHECK(vec.at(3)->getType() == EObjectType::Resistor);
		BOOST_CHECK(vec.at(4)->getType() == EObjectType::Inductor);
		BOOST_CHECK(vec.at(5)->getType() == EObjectType::Switch);

	}

	BOOST_AUTO_TEST_CASE( ValueAndDimension )
	{
		const std::string strVal = "3.1415926535897932384626433832795";
		const cpp_float floatVal = cpp_float(strVal);

		//there can be any other class derived from EObject escape Switch
		Resistor r(strVal);

			BOOST_CHECK_EQUAL( r.getValue(), floatVal );

		r.setDimension(Dimension::Normal);

			BOOST_CHECK_EQUAL( r.getValue(), floatVal );

		r.setDimension(Dimension::Kilo);

			BOOST_CHECK_EQUAL( r.getValue(), floatVal *
				pow(cpp_float("10"), static_cast<double>(Dimension::Kilo)) );

		r.setDimension(Dimension::Femto);

			BOOST_CHECK_EQUAL( r.getValue(), floatVal *
				pow(cpp_float("10"), static_cast<double>(Dimension::Femto)) );
	}

	BOOST_AUTO_TEST_CASE( checSourceClass )
	{
		const std::string strVal = "3.1415926535897932384626433832795";
		const cpp_float floatVal = cpp_float(strVal);

		//there can be SourceOfCurrent too
		SourceOfElectricity src(strVal);

			BOOST_CHECK_EQUAL(src.getValue(), floatVal);

		src.setDirection('-');

			BOOST_CHECK_EQUAL(src.getDirection(), -1);

		src.setDirection('+');

			BOOST_CHECK_EQUAL(src.getDirection(), 1);
	}

	BOOST_AUTO_TEST_CASE( testSwitch )
	{
		Switch s(true);

			BOOST_REQUIRE(s.getValue() == Switch::ON);

		s.setState(false);

			BOOST_REQUIRE(s.getValue() == Switch::OFF);

		s.setState(true);

			BOOST_REQUIRE(s.getValue() == Switch::ON);
	}


BOOST_AUTO_TEST_SUITE_END()
