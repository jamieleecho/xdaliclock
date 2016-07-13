#ifndef _time_c
#define _time_c

#include "time.h"
#include "coco.h"


// Last time that the time was updated.
struct timeval _lastTime;
UInt32 _xsecsUntilNextSecond = UInt32Init(0, 60);

// Maps a 0 based month to the number of days in that month in a non-leap year.
byte _daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


/**
 * @param year year in question
 * @return whether or not year is a leap year.
 */
byte timeIsLeapYear(unsigned year) {
  if (year % 4)
    return FALSE;
  if (year % 100)
    return TRUE;
  if (year % 400)
    return FALSE;
  return TRUE;
}


/**
 * Should be invoked periodically (at least once every 10 minutes or so) to
 * ensure proper time keeping.
 */
UInt32 _one = UInt32Init(0, 1);
UInt32 _sixty = UInt32Init(0, 60);
void timeTick() {
  unsigned timeLow = getTimer();
  if (timeLow < _lastTime.tv_xsec.Lo) {
    _lastTime.tv_xsec.Hi++;
  }
  _lastTime.tv_xsec.Lo = timeLow;

  // Increment seconds
  while(UInt32GreaterThanOrEqualTo(&_lastTime.tv_xsec, &_xsecsUntilNextSecond)) {
    UInt32Add(&_xsecsUntilNextSecond, &_xsecsUntilNextSecond, &_sixty);
    UInt32Add(&_lastTime.tv_sec, &_one, &_lastTime.tv_sec);
    _lastTime.tm.tm_sec++;

    // If seconds overflow, increment minutes
    if (_lastTime.tm.tm_sec >= 60) {
      _lastTime.tm.tm_sec = 0;
      _lastTime.tm.tm_min++;

      // If minutes overflow, increment hours
      if (_lastTime.tm.tm_min >= 60) {
        _lastTime.tm.tm_min = 0;
        _lastTime.tm.tm_hour++;

        // If hours overflow, increment days
        if (_lastTime.tm.tm_hour >= 24) {
          _lastTime.tm.tm_hour = 0;
          _lastTime.tm.tm_mday++;

          // If days overflow, increment months
          byte numDays = _daysPerMonth[_lastTime.tm.tm_mon];
          if (_lastTime.tm.tm_mon == 1 && timeIsLeapYear(_lastTime.tm.tm_year)) {
            numDays++;
          }
          if (_lastTime.tm.tm_mday > numDays) {
            _lastTime.tm.tm_mday = 1;
            _lastTime.tm.tm_mon++;
          }

          // If months overflow, increment years
          if (_lastTime.tm.tm_mon > 11) {
            _lastTime.tm.tm_mon = 0;
            _lastTime.tm.tm_year++;
          }
        }
      }
    }
  }
}


void gettimeofday(struct timeval *now, struct timezone *tzp) {
  timeTick();
  memcpy(now, &_lastTime, sizeof(struct timeval));
}


struct tm *localtime (struct timeval *tv) {
  return &tv->tm;
}


/**
 * Sets the current time.
 * @param year current year
 * @param month 1 based month
 * @param day 1 based day
 * @param hour 0 based 24-hour cycle hour
 * @param minute 0 based minute
 * @param seconds 0 based seconds
 * @return TRUE
 */
byte timeSet(unsigned year, byte month, byte day, byte hour, byte minute, byte seconds) {
  _lastTime.tv_xsec.Hi = _lastTime.tv_xsec.Lo = 0;
  _lastTime.tv_sec.Hi = _lastTime.tv_sec.Lo = 0;
  _lastTime.tm.tm_year = year;
  _lastTime.tm.tm_mon = month;
  _lastTime.tm.tm_mday = day;
  _lastTime.tm.tm_hour = hour;
  _lastTime.tm.tm_min = minute;
  _lastTime.tm.tm_sec = seconds;
  return TRUE;
}


byte __timeInit = timeSet(2016, 6, 26, 18, 23, 0);


#endif
