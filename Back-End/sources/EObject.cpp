#include <EObject.hpp>

EObject::EObject(const std::string& value,
				 Dimension dimension) :
	mValue(value),
	mDimension(dimension)
{

}

void EObject::setValue(const std::string& value)
{
	mValue = value;;
}

cpp_float EObject::getValue() const
{
	return cpp_float(mValue) *
		pow(cpp_float("10"),
			static_cast<cpp_float>(mDimension) );
}

void EObject::setDimension(Dimension dimension)
{
	mDimension = dimension;
}

const std::string& EObject::getString() const
{
	return mValue;
}
