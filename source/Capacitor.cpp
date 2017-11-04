#include <Capacitor.hpp>

Capacitor::Capacitor(double capacity) :
	EObject(capacity)
{

}

EObjectType Capacitor::getType() const
{
	return EObjectType::Capacitor;
}
