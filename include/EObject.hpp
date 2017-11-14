#ifndef EOBJECT_HPP_INCLUDED
#define EOBJECT_HPP_INCLUDED

#include <Dimension.hpp>
#include <EObjectType.hpp>
#include <static.hpp>
#include <string>

class EObject
{
	public:
		EObject(const std::string&, Dimension = Dimension::Normal);
		virtual ~EObject() = default;
		virtual EObjectType getType() const = 0;

		cpp_float getValue() const;
		void setValue(const std::string& value);
		const std::string& getString() const;
		void setDimension(Dimension);
		virtual void setCurrent(const cpp_float&) = 0;
		std::string getDimension() const;
		void setDimension(const std::string&);

		EObject(const EObject&) = delete;
		EObject& operator=(const EObject&) = delete;

	private:
		Dimension mDimension;
		std::string mValue;
};

#endif
