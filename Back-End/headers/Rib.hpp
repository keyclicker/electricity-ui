#ifndef RIB_HPP_INCLUDED
#define RIB_HPP_INCLUDED

#include <EObjectType.hpp>
#include <EObject.hpp>

#include <vector>

class Rib
{
    public:
        Rib();
        Rib(std::size_t u, std::size_t v);
		~Rib();
		void setPoints(std::size_t, std::size_t) const;
		bool getUsed() const;

        std::size_t getAnother(std::size_t u) const;
		cpp_float getVoltage(std::size_t u) const;
		cpp_float getResistance() const;
		cpp_float getCurrent() const;
		double defCurrDirection(std::size_t) const;

        friend std::istream& operator>>(std::istream& lhs,
                                        Rib& rhs);

    private:
        template<class T, class... Tn>
        void addElement(Tn&&... args);

    private:
		mutable std::size_t mU;
		mutable std::size_t mV;
		std::vector<EObject*> mElements;
		friend class TestSuite;
};

#endif
