#ifndef EOBJECT_HPP_INCLUDED
#define EOBJECT_HPP_INCLUDED

#include <Dimension.hpp>
#include <EObjectType.hpp>
#include <static.hpp>

class EObject
{
    public:
		EObject(double, Dimension = Dimension::Normal);

		virtual ~EObject() = default;
		virtual EObjectType getType() const = 0;

		const cpp_float& getValue() const;
		void setValue(double);

		void setDimension(Dimension);

		EObject(const EObject&) = delete;
		EObject& operator=(const EObject&) = delete;

	private:
		Dimension mDimension;
		cpp_float mValue;
};

#endif // EOBJECT_HPP_INCLUDED
