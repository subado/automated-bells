#pragma once

#include <RTClib.h>
#include <Wire.h>

#include <functional>
#include <memory>

typedef std::function<void(const DateTime &dateTime)> EventHandlerFunction;

class EventClock
{
public:
	EventClock();
	EventClock(TwoWire &wire);

	void setAlarm(const DateTime &dateTime, EventHandlerFunction handler);
	void setInterval(const TimeSpan &timeSpan, EventHandlerFunction handler);

	void handleEvents();

	class Event
	{
	public:
		Event(EventHandlerFunction handler);

		virtual bool isHappen() const = 0;
		virtual void run();

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
		void run() override;

		TimeSpan timeSpan;
		DateTime prevTime;
	};

private:
	TwoWire _wire;
	std::vector<std::unique_ptr<Event>> _events;
};
