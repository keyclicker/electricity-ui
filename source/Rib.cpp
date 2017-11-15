#include <Rib.hpp>

#include <SourceOfElectricity.hpp>
#include <SourceOfCurrent.hpp>
#include <Capacitor.hpp>
#include <Inductor.hpp>
#include <Resistor.hpp>
#include <Switcher.hpp>

#include <iostream>
#include <istream>
#include <utility>

#include <Debug.hpp>

const std::size_t maxCount = 320;

void Rib::addElement(EObject* obj)
{
	mElements.push_back( obj );
}

Rib::Rib(std::size_t u, std::size_t v) :
    mU(u),
	mV(v)
{
	if (mU >= maxCount || mV >= maxCount)
		throw std::logic_error("Rib::Rib(std::size_t, std::size_t): This scheme cant be calculated. "
							   "Count of potentials overflows.");
}

cpp_float Rib::getResistance() const
{
	if (mU == maxCount && mV == maxCount)
		throw std::logic_error("Rib::getResistance(): Rib is empty.");

	cpp_float resistane("0.0");

		for (const auto& i : mElements)
			if (i->getType() == EObjectType::Resistor)
				resistane += i->getValue();

	return resistane;
}

cpp_float Rib::getVoltage(std::size_t u) const
{
	if (mU == maxCount && mV == maxCount)
		throw std::logic_error("Rib::getVoltage(std::size_t): Rib is empty.");

	if (u != mU && u != mV)
		throw std::logic_error("Rib::getVoltage(std::size_t): Coutpoint " + std::to_string(u + 1) +
							   " doesn't belong to this rib.");

	cpp_float voltage("0.0");

        for (const auto& i : mElements)
            if (i->getType() ==
                EObjectType::SourceOfElectricity)
            {
                try
                {
					const auto& e = static_cast<SourceOfElectricity*>(i);

                    if (u == mU)
						voltage += e->getDirection() * e->getValue();
                    else
						voltage += -e->getDirection() * e->getValue();
                }
                catch(std::bad_cast& e)
                {
					std::cerr << e.what() << " " << __FILE__ << " " << __LINE__;
                }
            }

    return voltage;
}

cpp_float Rib::getCurrent() const
{
	if (mU == maxCount && mV == maxCount)
		throw std::logic_error("Rib::getCurrent(): Rib is empty.");

	cpp_float current("0.0");

		for (const auto& i : mElements)
			if (i->getType() == EObjectType::SourceOfCurrent)
				current += i->getValue();

	return current;
}

std::size_t Rib::getAnother(std::size_t u) const
{
	if (u != mU && u != mV)
		throw std::logic_error("Rib::getAnother(std::size_t): "
							   "Count point " + std::to_string(u + 1) +
							   " dosn't belong to rib " +
							   std::to_string(1 + mU) + " and " +
							   std::to_string(1 + mV) + ".");
    return (mU == u)? mV : mU;
}

Rib::Rib() :
	mU(maxCount),
	mV(maxCount)
{

}

void Rib::setPoints(std::size_t u, std::size_t v) const
{
	if (u >= maxCount || v >= maxCount)
		throw std::logic_error("Rib::setPoints(std::size_t, std::size_t): "
							   "This scheme cant be calculated. "
							   "Count of coutpoint overflows.");

	mU = u;
	mV = v;
}

double Rib::defCurrDirection(std::size_t u) const
{
	if (u != mU && u != mV)
		throw std::logic_error("Rib::getAnother(std::size_t): "
							   "Count point " + std::to_string(u + 1) +
							   " dosn't belong to rib " +
							   std::to_string(1 + mU) + " and " +
							   std::to_string(1 + mV) + ".");

	return (mU == u)? 1.0 : -1.0;
}

bool Rib::getUsed() const
{
	for (const auto& i : mElements)
		if ( i->getType() == EObjectType::Capacitor ||
			(i->getType() == EObjectType::Switch && i->getValue() == Switch::OFF) )
		{
			return false;
		}

	return true;
}

