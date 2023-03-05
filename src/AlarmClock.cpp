#include "AlarmClock.hpp"
#include "Rtc.hpp"

extern Rtc rtc;

AlarmClock::AlarmClock()
: wire_ { Wire }
{
}

AlarmClock::AlarmClock(TwoWire &wire)
: wire_ { wire }
{
}

void AlarmClock::on(const Time &time, AlarmHandlerFunction handler, const uint32_t &duration)
{
	alarms_.push_back(Alarm(time, AlarmHandlerFunction(handler)));
}

void AlarmClock::handleAlarms()
{
	for (auto &alarm : alarms_)
	{
		if (alarm.time == rtc.now())
		{
			if (!alarm.runned)
			{
				alarm.runned = true;
				alarm.startTime = millis();

				alarm.handler(alarm.time);
			}
			else if (alarm.runned && (millis() - alarm.startTime == alarm.duration))
			{
				alarm.runned = false;
			}
		}
	}
}

AlarmClock::Alarm::Alarm(const Time &time, AlarmHandlerFunction handler, const uint32_t &duration)
: time { time },
handler { handler },
duration { duration }
{
}
