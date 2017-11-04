#ifndef SOURCEOFCURRENT_HPP_INCLUDED
#define SOURCEOFCURRENT_HPP_INCLUDED

#include <Counter.hpp>
#include <EObject.hpp>

class SourceOfCurrent : public EObject,
						public Counter<SourceOfCurrent>
{
	public:
		SourceOfCurrent(double, char, Dimension = Dimension::Normal);
		EObjectType getType() const override;
		int getDirection() const;
		void setDirection(char);

	private:
		int mDirection;
};


#endif // EOBJECT_HPP_INCLUDED
