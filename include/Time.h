#ifndef TIME_H
#define TIME_H

#include <Arduino.h>
#include <DS3231.h>

class Time
{
public:

	Time(const DateTime &dateTime);

	uint8_t hour() const;
	uint8_t minute() const;

	Time& operator=(const DateTime &dateTime);
	Time& operator=(const String &str);

	operator String() const;

protected:

	String unitToString(uint8_t unit) const;

	uint8_t hour_, minute_;
};

#endif // TIME_H
