#pragma once

#include <RTClib.h>
#include <Wire.h>

#include <functional>
#include <memory>

typedef std::function<void(const DateTime &dateTime)> EventHandlerFunction;

class AlarmClock
{
public:
	AlarmClock();
	AlarmClock(TwoWire &wire);

	void setAlarm(const DateTime &dateTime, EventHandlerFunction handler);
	void setInterval(const TimeSpan &timeSpan, EventHandlerFunction handler);

	void handleEvents();

	class Event
	{
	public:
		Event(EventHandlerFunction handler, uint32_t startTime = 0);

		virtual bool isHappen() const = 0;

		EventHandlerFunction handler;
		uint32_t startTime;
		bool runned = false;
	};

	class Alarm : public Event
	{
	public:
		Alarm(const DateTime &dateTime, EventHandlerFunction handler);

		bool isHappen() const override;

		DateTime dateTime;
	};

	class Interval : public Event
	{
	public:
		Interval(const TimeSpan &timeSpan, EventHandlerFunction handler);

		bool isHappen() const override;

		TimeSpan timeSpan;
	};

private:
	TwoWire wire_;
	std::vector<std::unique_ptr<Event>> events_;
};
