#ifndef ALARM_CLOCK_HPP
#define ALARM_CLOCK_HPP

#include <Wire.h>

#include <functional>
#include <map>

#include "Time.hpp"

typedef std::function<void(const Time &time)> AlarmHandlerFunction;

class AlarmClock
{
public:

	AlarmClock();
	AlarmClock(TwoWire &wire);

	void on(const Time &time, AlarmHandlerFunction handler);

	void handleAlarms();

private:

	TwoWire wire_;
	std::map<Time, AlarmHandlerFunction*> alarms_;

};

#endif // ALARM_CLOCK_HPP
