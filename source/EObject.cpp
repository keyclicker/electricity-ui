#include <EObject.hpp>
#include <cassert>
#include <cmath>

EObject::EObject(double value,
				 Dimension dimension) :
	mValue(value),
	mDimension(dimension)
{

}

void EObject::setValue(double value)
{
	mValue = value * cpp_float( static_cast<double>(mDimension) );
}

const cpp_float& EObject::getValue() const
{
	return mValue;
}

void EObject::setDimension(Dimension dimension)
{
	mDimension = dimension;
}
