#include <AlarmClock.hpp>
#include <Rtc.hpp>

extern Rtc rtc;

AlarmClock::AlarmClock() : wire_{Wire}
{
}

AlarmClock::AlarmClock(TwoWire &wire) : wire_{wire}
{
}

void AlarmClock::setAlarm(const DateTime &dateTime, EventHandlerFunction handler)
{
	events_.emplace_back(std::make_unique<Alarm>(dateTime, handler));
}

void AlarmClock::setInterval(const TimeSpan &timeSpan, EventHandlerFunction handler)
{
	events_.emplace_back(std::make_unique<Interval>(timeSpan, handler));
}

void AlarmClock::handleEvents()
{
	for (auto &event : events_)
	{
		if (event->isHappen())
		{
			if (!event->runned)
			{
				event->runned = true;
				event->startTime = rtc.now().secondstime();

				event->handler(rtc.now());
			}
			else if (event->runned && (rtc.now().secondstime() - event->startTime >= 1))
			{
				event->runned = false;
			}
		}
	}
}

AlarmClock::Event::Event(EventHandlerFunction handler, uint32_t startTime)
	: handler{handler}, startTime{startTime}
{
}

AlarmClock::Alarm::Alarm(const DateTime &dateTime, EventHandlerFunction handler)
	: Event(handler), dateTime{dateTime}
{
}

bool AlarmClock::Alarm::isHappen() const
{
	if (dateTime == rtc.now())
	{
		return true;
	}
	return false;
}

AlarmClock::Interval::Interval(const TimeSpan &timeSpan, EventHandlerFunction handler)
	: Event(handler, rtc.now().secondstime()), timeSpan{timeSpan}
{
}

bool AlarmClock::Interval::isHappen() const
{
	if (startTime + timeSpan.totalseconds() == rtc.now().secondstime())
	{
		return true;
	}
	return false;
}
