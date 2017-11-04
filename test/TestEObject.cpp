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

BOOST_AUTO_TEST_SUITE( Test )

	BOOST_AUTO_TEST_CASE( checkType )
	{
		std::vector<std::unique_ptr<EObject>> vec;

		vec.emplace_back(std::make_unique<SourceOfElectricity>(1.0));
		vec.emplace_back(std::make_unique<SourceOfCurrent>(1.0));
		vec.emplace_back(std::make_unique<Capacitor>(1.0));
		vec.emplace_back(std::make_unique<Resistor>(1.0));
		vec.emplace_back(std::make_unique<Inductor>(1.0));

			BOOST_CHECK(vec.at(0)->getType() == EObjectType::SourceOfElectricity);
			BOOST_CHECK(vec.at(1)->getType() == EObjectType::SourceOfCurrent);
			BOOST_CHECK(vec.at(2)->getType() == EObjectType::Capacitor);
			BOOST_CHECK(vec.at(3)->getType() == EObjectType::Resistor);
			BOOST_CHECK(vec.at(4)->getType() == EObjectType::Inductor);
	}

	BOOST_AUTO_TEST_CASE( ValueAndDimension )
	{
		//here can be any other class derived from EObject, i've chosen Resistor
		std::unique_ptr<EObject> R =
				std::make_unique<Resistor>(50.0, Dimension::Kilo);

			BOOST_CHECK_EQUAL(R->getValue(), 50.0 * std::pow(10, 3));

		R->setValue(3.141592);
		R->setDimension(Dimension::Normal);

			BOOST_CHECK_EQUAL(R->getValue(), 3.141592);

		R->setDimension(Dimension::Mega);

			BOOST_CHECK_EQUAL(R->getValue(), 3141592);
	}

	BOOST_AUTO_TEST_CASE( checkVoltageSource )
	{
		SourceOfElectricity src(1.0);

			BOOST_CHECK_EQUAL(src.getDirection(), 1);
			BOOST_CHECK_EQUAL(src.getValue(), 1.0);

		src.setDirection('-');

			BOOST_CHECK_EQUAL(src.getDirection(), -1);

			BOOST_CHECK_THROW(src.setDirection('5'), std::logic_error);
	}


BOOST_AUTO_TEST_SUITE_END()
