/* xdaliclock - a melting digital clock
 * Copyright (c) 1991-2010 Jamie Zawinski <jwz@jwz.org>
 * CoCo Version - Copyright (c) 2016 Jamie Cho <jamieleecho@gmail.com>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  No representations are made about the suitability of this
 * software for any purpose.  It is provided "as is" without express or
 * implied warranty.
 */


#include <coco.h>

#include "c_stuff.h"
#include "digital.h"
#include "time.h"
#include "UInt32.h"


struct simple_date_time {
  unsigned int year;
  byte month;
  byte day;
  byte hour;
  byte minute;
  byte second;
  unsigned int marker;
};

struct dali_config daliConfig;

// User entered date and time
struct simple_date_time *dateTime = 0xe00;

byte MyInkey() {
  byte *pia1a = 0xff00;
  byte *pia1b = 0xff02;

  // Is space pressed?
  *pia1b = 0x7f;
  if ((*pia1a & 0x8) == 0) {
    return ' ';
  }

  // is 6 pressed?
  *pia1b = 0xbf;
  if ((*pia1a & 0x10) == 0) {
    return '6';
  }

  // is 5 pressed?
  *pia1b = 0xdf;
  if ((*pia1a & 0x10) == 0) {
    return '5';
  }

  // is 4 pressed?
  *pia1b = 0xef;
  if ((*pia1a & 0x10) == 0) {
    return '4';
  }

  // is 3 pressed?
  *pia1b = 0xf7;
  if ((*pia1a & 0x10) == 0) {
    return '3';
  }

  // is 2 pressed?
  *pia1b = 0xfb;
  if ((*pia1a & 0x10) == 0) {
    return '2';
  }

  // is 1 pressed?
  *pia1b = 0xfd;
  if ((*pia1a & 0x10) == 0) {
    return '1';
  }

  // is 0 pressed?
  *pia1b = 0xfe;
  if ((*pia1a & 0x10) == 0) {
    return '0';
  }

  return 0;
}


int main () {
  initCoCoSupport();
  heapInit();
  timeInit();
  setHighSpeed(TRUE);
  width(32);

  if (dateTime->marker = 0x1234) {
    timeSet(dateTime->year, dateTime->month, dateTime->day, dateTime->hour,
            dateTime->minute, dateTime->second);
  }

  daliConfig.width = 256;
  daliConfig.height = 192;
  daliConfig.bitmap = 0xe00;
  daliConfig.max_fps = 30;
  daliConfig.max_cps = 30;
  daliConfig.render_state = 0;
  daliConfig.time_mode = HHMMSS;
  daliConfig.date_mode = MMDDYY;
  daliConfig.display_date_p = 0;
  daliConfig.test_hack = 0;

  render_init(&daliConfig);
  memset(daliConfig.bitmap, 0xff, 6144);
  showGraphicsAddress(7);
  showPmode4(1);

  UInt32 displayTimeTime;
  UInt32 five = UInt32Init(0, 5);
  struct timeval now;
  struct timezone tzp;

  while(TRUE) {
    // Revert to time display if time
    if (daliConfig.display_date_p) {
      gettimeofday(&now, &tzp);
      if (UInt32GreaterThan(&now.tv_sec, &displayTimeTime)) {
        daliConfig.display_date_p = FALSE;
      }
    }

    byte a = MyInkey();
    switch(a) {
      case '0':
        daliConfig.time_mode = HHMMSS;
        daliConfig.date_mode = MMDDYY;
        break;

      case '1':
        daliConfig.time_mode = HHMMSS;
        break;

      case '2':
        daliConfig.time_mode = HHMM;
        break;

      case '3':
        daliConfig.time_mode = SS;
        break;

      case '4':
        daliConfig.date_mode = MMDDYY;
        break;

      case '5':
        daliConfig.date_mode = DDMMYY;
        break;

      case '6':
        daliConfig.date_mode = YYMMDD;
        break;

      case ' ':
        daliConfig.display_date_p = TRUE;
        gettimeofday(&now, &tzp);
        UInt32Add(&displayTimeTime, &now.tv_sec, &five);
        break;
    }

    render_once(&daliConfig);
  }

  return 0;
}
