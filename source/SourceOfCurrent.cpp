#include <SourceOfCurrent.hpp>
#include <stdexcept>

SourceOfCurrent::SourceOfCurrent(const std::string& current,
								 char direction,
								 Dimension dimension) :
	EObject(current, dimension),
	mDirection(direction)
{
	if (direction != '+' && direction != '-')
		throw std::logic_error("SrcOfCurr::SrcOfCurr(): "
							   "Direction can be only + or - ");
}

EObjectType SourceOfCurrent::getType() const
{
	return EObjectType::SourceOfCurrent;
}

int SourceOfCurrent::getDirection() const
{
	return (mDirection == '+')? 1 : -1;
}

void SourceOfCurrent::setDirection(char direction)
{
	if (direction != '+' && direction != '-')
		throw std::logic_error("SrcOfCurr::setDirection(char): "
							   "Direction can be only + or - ");

	mDirection = direction;
}


