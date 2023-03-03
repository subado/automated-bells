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

	void on(const Time &time, AlarmHandlerFunction handler, const uint32_t &duration = 1000);

	void handleAlarms();

	class Alarm
	{
	public:

		Alarm(const Time &time, AlarmHandlerFunction handler, const uint32_t &duration = 1000);

		Time time;
		AlarmHandlerFunction handler;
		uint32_t duration;
		uint32_t startTime;
		bool runned = false;

	};

private:

	TwoWire wire_;
	std::vector<Alarm> alarms_;

};

#endif // ALARM_CLOCK_HPP
