#ifndef SOURCEOFELECTRICITY_HPP_INCLUDED
#define SOURCEOFELECTRICITY_HPP_INCLUDED

#include <EObject.hpp>
#include <GObject.h>
#include <Counter.hpp>

#include <string>

class SourceOfElectricity : public EObject,
							public GObject,
							public Counter<SourceOfElectricity>
{
    public:
		SourceOfElectricity(const std::string& = "52983852389857",
			char = '+', Dimension = Dimension::Normal);
        EObjectType getType() const override;
        int getDirection() const;
		void setDirection(char);
		void setDirection(const Point*);
		void setCurrent(const cpp_float&) override;

    private:
		char mDirection;
};

#endif
