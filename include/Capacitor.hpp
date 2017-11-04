#ifndef CAPACITOR_HPP_INCLUDED
#define CAPACITOR_HPP_INCLUDED

#include <EObject.hpp>
#include <Counter.hpp>

class Capacitor : public EObject,
				  public Counter<Capacitor>
{
    public:
		Capacitor(double);
        EObjectType getType() const override;
};


#endif // CAPACITOR_HPP_INCLUDED
