#include <SourceOfElectricity.hpp>
#include <stdexcept>

SourceOfElectricity::SourceOfElectricity( const std::string& voltage,
										  char direction,
										  Dimension dimension) :
	EObject(voltage, dimension),
	mDirection(direction)
{
	if (direction != '+' && direction != '-')
		throw std::logic_error("SrcOfEl::SrcOfEl(): "
							   "Direction can be only + or - ");
}

EObjectType SourceOfElectricity::getType() const
{
    return EObjectType::SourceOfElectricity;
}

int SourceOfElectricity::getDirection() const
{
	return (mDirection == '+')? 1 : -1;
}

void SourceOfElectricity::setDirection(char direction)
{
	if (direction != '+' && direction != '-')
		throw std::logic_error("SrcOfEl::setDirection(char):"
							   "Direction can be only + or - ");

	mDirection = direction;
}
