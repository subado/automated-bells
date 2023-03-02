#include "Time.hpp"

Time::Time(const DateTime &dateTime)
: hour_ { dateTime.hour() },
minute_ { dateTime.minute() },
second_ { dateTime.second() }
{
}

Time::Time(const String &str)
: hour_ { stringToUnit(str.substring(0, str.indexOf(":"))) },
minute_ { stringToUnit(str.substring(str.indexOf(":") + 1, str.lastIndexOf(":"))) },
second_ { stringToUnit(str.substring(str.lastIndexOf(":") + 1, str.length())) }
{
	Serial.println(hour_);
	Serial.println(minute_);
	Serial.println(second_);
}

uint8_t Time::hour() const
{
	return hour_;
}

uint8_t Time::minute() const
{
	return minute_;
}

uint32_t Time::toLong() const
{
	return hour_ * 60 * 60 + minute_ * 60 + second_;
}

Time& Time::operator=(const DateTime &dateTime)
{
	hour_ = dateTime.hour();
	minute_ = dateTime.minute();
	second_ = dateTime.second();

	return *this;
}

Time& Time::operator=(const String &str)
{
	hour_ = stringToUnit(str.substring(0, str.indexOf(":")));
	minute_ = stringToUnit(str.substring(str.indexOf(":") + 1, str.lastIndexOf(":")));
	second_ = stringToUnit(str.substring(str.lastIndexOf(":") + 1, str.length()));

	return *this;
}

bool operator==(const Time &time, const DateTime &dateTime)
{
	if (time.hour_ == dateTime.hour() && time.minute_ == dateTime.minute() && time.second_ == dateTime.second())
	{
		return true;
	}
	return false;
}

bool operator==(const DateTime &dateTime, const Time &time)
{
	return (time == dateTime);
}

bool operator>(const Time &time1, const Time &time2)
{
	if (time1.toLong() > time2.toLong())
	{
		return true;
	}
	return false;
}

bool operator<(const Time &time1, const Time &time2)
{
	if (time1.toLong() < time2.toLong())
	{
		return true;
	}
	return false;
}

Time::operator String() const
{
	return unitToString(hour_) + ":" + unitToString(minute_) + ":" + unitToString(second_);
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
