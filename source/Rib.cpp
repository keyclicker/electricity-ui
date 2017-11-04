#include <Rib.hpp>

#include <SourceOfElectricity.hpp>
#include <SourceOfCurrent.hpp>
#include <Capacitor.hpp>
#include <Inductor.hpp>
#include <Resistor.hpp>

#include <type_traits>
#include <iostream>
#include <istream>
#include <utility>
#include <cassert>

static EObjectType fromChar(char ch)
{
	switch(ch)
	{
		case 'E':
		{
			return EObjectType::SourceOfElectricity;
			break;
		}

		case 'R':
		{
			return EObjectType::Resistor;
			break;
		}

		case 'I':
		{
			return EObjectType::SourceOfCurrent;
			break;
		}

		case 'C':
		{
			return EObjectType::Capacitor;
			break;
		}

		case 'L':
		{
			return EObjectType::Inductor;
			break;
		}

		default:
			throw std::logic_error("Rib.cpp fromChar: Undefined symbol -> " + ch);
	}
}

const std::size_t maxCount = 320;

template<class T, class... Tn>
void Rib::addElement(Tn&&... args)
{
    static_assert(std::is_base_of< EObject, std::decay_t<T> >::value &&
                  !std::is_same< EObject, std::decay_t<T> >::value,
				  "Argument must be inherited from EObject.");

    std::unique_ptr<EObject> pobj =
        std::make_unique<T>(
            std::forward<Tn>(args)...);

    mElements.emplace_back( std::move(pobj) );
}

std::istream& operator>>(std::istream& lhs,
                         Rib& rhs)
{
	if (rhs.mU == maxCount && rhs.mV == maxCount)
		throw std::logic_error("Rib::operator>>: Empty rib.");

	std::size_t num;
        lhs >> num;

	try
	{
		for (std::size_t i = 0; i < num; ++i)
		{
			char typeInString;
				lhs >> typeInString;

			auto type = fromChar(typeInString);

			switch(type)
			{
				case EObjectType::Resistor:
				{
					double resistance{};
						lhs >> resistance;
	
	                rhs.addElement<Resistor>(resistance);
					break;
				}
	
				case EObjectType::SourceOfElectricity:
				{
					double voltage{};
					char direction;
						lhs >> voltage >> direction;
	
					rhs.addElement<SourceOfElectricity>( voltage, direction );
	                break;
	            }

				case EObjectType::Capacitor:
				{
					double capacity{};
						lhs >> capacity;

					rhs.addElement<Capacitor>(capacity);
					break;
				}

				case EObjectType::SourceOfCurrent:
				{
					double current{};
					char direction;
						lhs >> current >> direction;
					rhs.addElement<SourceOfCurrent>(current, direction);
					break;
				}

				case EObjectType::Inductor:
				{
					double induction{};
						lhs >> induction;

					rhs.addElement<Inductor>(induction);
					break;
				}

				default:
				{
					//
					break;
				}
			}//switch
		}//for
	}//try-catch
	catch(std::logic_error& e)
	{
		throw;
	}

    return lhs;
}

Rib::Rib(std::size_t u, std::size_t v) :
    mU(u),
	mV(v),
	mUsed(false)
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
                    const auto& e = static_cast<SourceOfElectricity*>(i.get());

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
	mV(maxCount),
	mUsed(false)
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
	return mUsed;
}

void Rib::setUsed(bool used)
{
	mUsed = used;
}
