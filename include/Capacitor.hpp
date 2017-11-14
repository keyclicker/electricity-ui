#ifndef CAPACITOR_HPP_INCLUDED
#define CAPACITOR_HPP_INCLUDED

#include <EObject.hpp>
#include <GObject.h>
#include <Counter.hpp>

class Capacitor : public EObject,
				  public GObject,
				  public Counter<Capacitor>
{
    public:
		Capacitor(const std::string& = "1",
			Dimension = Dimension::Nano);
		~Capacitor();
        EObjectType getType() const override;
		void getInput() override;
		void setCurrent(const cpp_float&) override;
};


#endif
