#ifndef RIB_HPP_INCLUDED
#define RIB_HPP_INCLUDED

#include <EObjectType.hpp>
#include <EObject.hpp>

#include <vector>
#include <memory>

class Rib
{
    public:
        Rib();
        Rib(std::size_t u, std::size_t v);
		void setPoints(std::size_t, std::size_t) const;
		void setUsed(bool);
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
        std::vector< std::unique_ptr<EObject> >
            mElements;
		mutable bool mUsed;

		friend class TestSuite;
};

#endif // RIB_HPP_INCLUDED
