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

std::string EObject::getDimension() const
{
	if (mDimension == Dimension::Femto)
		return "Femto";
	if (mDimension == Dimension::Giga)
		return "Giga";
	if (mDimension == Dimension::Kilo)
		return "Kilo";
	if (mDimension == Dimension::Mega)
		return "Mega";
	if (mDimension == Dimension::Micro)
		return "Micro";
	if (mDimension == Dimension::Milli)
		return "Milli";
	if (mDimension == Dimension::Nano)
		return "Nano";
	if (mDimension == Dimension::Normal)
		return "Normal";
	if (mDimension == Dimension::Peta)
		return "Peta";
	if (mDimension == Dimension::Pico)
		return "Pico";
	if (mDimension == Dimension::Tera)
		return "Tera";
}

void EObject::setDimension(const std::string& d)
{
	if (d == "Femto")
		mDimension = Dimension::Femto;
	if (d == "Giga")
		mDimension = Dimension::Giga;
	if (d == "Kilo")
		mDimension = Dimension::Kilo;
	if (d == "Mega")
		mDimension = Dimension::Mega;
	if (d == "Micro")
		mDimension = Dimension::Micro;
	if (d == "Milli")
		mDimension = Dimension::Milli;
	if (d == "Nano")
		mDimension = Dimension::Nano;
	if (d == "Normal")
		mDimension = Dimension::Normal;
	if (d == "Peta")
		mDimension = Dimension::Peta;
	if (d == "Pico")
		mDimension = Dimension::Pico;
	if (d == "Tera")
		mDimension = Dimension::Tera;
}
