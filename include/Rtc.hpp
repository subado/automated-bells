#pragma once

#include <RTClib.h>

class Rtc
{
public:
	bool begin(int sda, int scl);

	DateTime now();
	void adjust(const DateTime &dt);

private:
#if defined(USE_DS3231)
	RTC_DS3231
#elif defined(USE_DS1307)
	RTC_DS1307
#elif defined(USE_PCF8563)
	RTC_PCF8563
#elif defined(USE_PCF8523)
	RTC_PCF8523
#endif
	_clock;
	TwoWire _wire;
};
