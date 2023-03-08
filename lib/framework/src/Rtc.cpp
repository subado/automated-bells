#include <Rtc.hpp>

bool Rtc::begin(int sda, int scl)
{
  _wire.begin(sda, scl);
  if (_clock.begin(&_wire))
  {
    return true;
  }
  return false;
}

DateTime Rtc::now()
{
  return _clock.now();
}

void Rtc::adjust(const DateTime &dt)
{
  _clock.adjust(dt);
}

Rtc rtc;
