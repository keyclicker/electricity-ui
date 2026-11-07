#ifndef METER_HPP_INCLUDED
#define METER_HPP_INCLUDED

#include <Resistor.hpp>

#include <QGraphicsSimpleTextItem>

// A measuring instrument: shows its reading on its display
class Meter : public Resistor
{
	public:
		Meter(const QString&, const std::string&);
		void getInput() final;

	protected:
		void showValue(const cpp_float&);

	private:
		QGraphicsSimpleTextItem* mDisplay;
};

#endif
