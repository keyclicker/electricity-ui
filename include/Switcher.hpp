#ifndef SWITCHER_HPP_INCLUDED
#define SWITCHER_HPP_INCLUDED

#include <EObject.hpp>
#include <GObject.h>
#include <Counter.hpp>

class Switch : public EObject,
			   public GObject,
			   public Counter<Switch>
{
	public:
		Switch(bool = true);
		EObjectType getType() const override;
		void setCurrent(const cpp_float&) override;
		void getInput() override;
		void setState(bool);

		static const cpp_float ON;
		static const cpp_float OFF;
};



#endif
