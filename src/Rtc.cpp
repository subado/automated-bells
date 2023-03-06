#include <Rtc.hpp>

Rtc::Rtc() : wire_{Wire}
{
	clock_.begin(&wire_);
}

Rtc::Rtc(int sda, int scl)
{
	wire_.begin(sda, scl);
	clock_.begin(&wire_);
}

DateTime Rtc::now()
{
	return clock_.now();
}

void Rtc::adjust(const DateTime &dateTime)
{
	clock_.adjust(dateTime);
}
