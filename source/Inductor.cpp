#include <Inductor.hpp>

Inductor::Inductor(double induction, Dimension dimension) :
	EObject(induction, dimension)
{

}

EObjectType Inductor::getType() const
{
	return EObjectType::Inductor;
}


