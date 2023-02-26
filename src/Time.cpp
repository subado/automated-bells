#include "Time.h"

Time::Time(const DateTime &dateTime)
{
	hour_ = dateTime.hour();
	minute_ = dateTime.minute();
}

uint8_t Time::hour() const
{
	return hour_;
}

uint8_t Time::minute() const
{
	return minute_;
}

Time& Time::operator=(const DateTime &dateTime)
{
	hour_ = dateTime.hour();
	minute_ = dateTime.minute();

	return *this;
}

Time& Time::operator=(const String &str)
{
	hour_ = str.substring(0, str.indexOf(":") - 1).toInt();
	minute_ = str.substring(str.indexOf(":"), str.length() - 1).toInt();
	return *this;
}

Time::operator String() const
{
	return unitToString(hour_) + ":" + unitToString(minute_);
}

String Time::unitToString(uint8_t unit) const
{
	String str;

	if (unit < 10)
	{
		str += "0";
	}
	str += String(unit, DEC);

	return str;
}
