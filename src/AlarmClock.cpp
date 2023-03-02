#include "AlarmClock.hpp"

AlarmClock::AlarmClock()
: wire_ { Wire }
{
}

AlarmClock::AlarmClock(TwoWire &wire)
: wire_ { wire }
{
}

void AlarmClock::on(const Time &time,AlarmHandlerFunction handler)
{
	alarms_.emplace(time, new AlarmHandlerFunction(handler));
}

void AlarmClock::handleAlarms()
{
	for (auto &alarm : alarms_)
	{
		if (alarm.first == RTClib::now(wire_))
		{
			(*alarm.second)(alarm.first);
		}
	}
}
