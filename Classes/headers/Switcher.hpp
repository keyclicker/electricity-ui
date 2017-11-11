#ifndef SWITCHER_HPP_INCLUDED
#define SWITCHER_HPP_INCLUDED

#include <EObject.hpp>
#include <Counter.hpp>

class Switch : public EObject,
			   public Counter<Switch>
{
	public:
		Switch(bool = true);
		EObjectType getType() const override;
		void setState(bool);

		static const cpp_float ON;
		static const cpp_float OFF;
};



#endif
