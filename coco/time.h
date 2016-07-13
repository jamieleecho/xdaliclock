#ifndef _time_h
#define _time_h

#include "c_stuff.h"
#include "UInt32.h"


typedef UInt32 time_t;


struct tm {
  byte tm_sec;
  byte tm_min;
  byte tm_hour;
  byte tm_mday;
  byte tm_mon;
  unsigned tm_year;
};


// Wanky definition of time. Includes total time in seconds and 60th of
// seconds since program start and formatted time. Time keeping is
// simplified when these structures are kept in sync. It does require
// that getimeofday() is called frequently enough (at least every 10
// minutes or so).
struct timeval {
  // Total time in seconds from when the program started
  time_t tv_sec;

  // Total time in 60ths of seconds from when the program
  // started
  time_t tv_xsec;

  // Formatted time
  struct tm tm;
};


struct timezone {
  byte __IGNORE;
};

void gettimeofday(struct timeval *now, struct timezone *tzp);
struct tm *localtime (struct timeval *time);
byte timeSet(unsigned year, byte month, byte day, byte hour, byte minute, byte seconds);

#endif
