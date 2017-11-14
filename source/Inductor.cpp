#include <Inductor.hpp>

Inductor::Inductor(const std::string& induction, Dimension dimension) :
	EObject(induction, dimension),
	GObject("Inductor")
{

}

EObjectType Inductor::getType() const
{
	return EObjectType::Inductor;
}


