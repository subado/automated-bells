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

	Time& operator=(const DateTime &dateTime);
	Time& operator=(const String &str);

	operator String() const;

protected:

	String unitToString(uint8_t unit) const;
	uint8_t stringToUnit(String str) const;

	uint8_t hour_, minute_;
};

#endif // TIME_HPP
