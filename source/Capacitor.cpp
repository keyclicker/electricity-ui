#include <Capacitor.hpp>

Capacitor::Capacitor(const std::string& capacity, Dimension dim) :
	EObject(capacity, dim)
{

}

EObjectType Capacitor::getType() const
{
	return EObjectType::Capacitor;
}
