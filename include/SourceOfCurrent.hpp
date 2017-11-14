#ifndef SOURCEOFCURRENT_HPP_INCLUDED
#define SOURCEOFCURRENT_HPP_INCLUDED

#include <Counter.hpp>
#include <EObject.hpp>
#include <GObject.h>

class SourceOfCurrent : public EObject,
						public GObject,
						public Counter<SourceOfCurrent>
{
	public:
		SourceOfCurrent(const std::string&,
			char = '+', Dimension = Dimension::Normal);
		EObjectType getType() const override;
		int getDirection() const;
		void setDirection(char);
		void setDirection(const Point*);

	private:
		int mDirection;
};


#endif
