#include <Inductor.hpp>

Inductor::Inductor(const std::string& induction, Dimension dimension) :
	EObject(induction, dimension)
{

}

EObjectType Inductor::getType() const
{
	return EObjectType::Inductor;
}


