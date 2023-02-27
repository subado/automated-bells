#include "Time.h"

Time::Time(const DateTime &dateTime)
: hour_ { dateTime.hour() },
minute_ { dateTime.minute() }
{
}

Time::Time(const String &str)
: hour_ { stringToUnit(str.substring(0, str.indexOf(":"))) },
minute_ { stringToUnit(str.substring(str.indexOf(":") + 1, str.length())) }
{
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
	hour_ = stringToUnit(str.substring(0, str.indexOf(":")));
	minute_ = stringToUnit(str.substring(str.indexOf(":") + 1, str.length()));

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

uint8_t Time::stringToUnit(String str) const
{
	if (str.startsWith("0") && str.length() > 1)
	{
		str.remove(str.indexOf("0"), 1);
	}

	return static_cast<uint8_t>(str.toInt());
}
