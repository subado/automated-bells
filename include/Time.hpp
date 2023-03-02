#ifndef TIME_HPP
#define TIME_HPP

#include <Arduino.h>
#include <DS3231.h>

class Time
{
public:

	Time(const DateTime &dateTime);
	Time(const String &str);

	uint8_t hour() const;
	uint8_t minute() const;
	uint8_t second() const;

	uint32_t toLong() const;

	Time& operator=(const DateTime &dateTime);
	Time& operator=(const String &str);

	friend bool operator==(const Time &time, const DateTime &dateTime);
	friend bool operator==(const DateTime &dateTime, const Time &time);

	friend bool operator>(const Time &time1, const Time &time2);
	friend bool operator<(const Time &time1, const Time &time2);

	operator String() const;

protected:

	String unitToString(uint8_t unit) const;
	uint8_t stringToUnit(String str) const;

	uint8_t hour_, minute_, second_;

};

#endif // TIME_HPP
