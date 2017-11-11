#ifndef SOURCEOFELECTRICITY_HPP_INCLUDED
#define SOURCEOFELECTRICITY_HPP_INCLUDED

#include <EObject.hpp>
#include <Counter.hpp>

#include <string>

class SourceOfElectricity : public Counter<SourceOfElectricity>,
                            public EObject
{
    public:
		SourceOfElectricity(const std::string&,
			char = '+', Dimension = Dimension::Normal);
        EObjectType getType() const override;
        int getDirection() const;
		void setDirection(char);

    private:
		char mDirection;
};

#endif
