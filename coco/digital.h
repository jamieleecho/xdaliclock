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

#ifndef _DIGITAL_H
#define _DIGITAL_H

#include <cmoc.h>
#include "c_stuff.h"
#include "time.h"

#include "xdaliclock.h"

#define DO_TEXTURE	/* Create LUMINANCE_ALPHA data instead of a bitmap */
#define BIGENDIAN	/* Bit ordering if creating a single-bit bitmap */

typedef unsigned byte POS;
typedef unsigned char BOOL;

/* static int use_builtin_font; */
struct raw_number {
  unsigned char *bits;
  POS width, height;
};

#define FONT(X)								\
 static struct raw_number numbers_ ## X [] = {			\
  { zero  ## X ## _bits,  zero ## X ## _width,  zero ## X ## _height }, \
  { one   ## X ## _bits,   one ## X ## _width,   one ## X ## _height }, \
  { two   ## X ## _bits,   two ## X ## _width,   two ## X ## _height }, \
  { three ## X ## _bits, three ## X ## _width, three ## X ## _height }, \
  { four  ## X ## _bits,  four ## X ## _width,  four ## X ## _height }, \
  { five  ## X ## _bits,  five ## X ## _width,  five ## X ## _height }, \
  { six   ## X ## _bits,   six ## X ## _width,   six ## X ## _height }, \
  { seven ## X ## _bits, seven ## X ## _width, seven ## X ## _height }, \
  { eight ## X ## _bits, eight ## X ## _width, eight ## X ## _height }, \
  { nine  ## X ## _bits,  nine ## X ## _width,  nine ## X ## _height }, \
  { colon ## X ## _bits, colon ## X ## _width, colon ## X ## _height }, \
  { slash ## X ## _bits, slash ## X ## _width, slash ## X ## _height }, \
  { 0, 0, 0 }								\
}

#undef countof
#define countof(x) (sizeof((x))/sizeof(*(x)))

/* Number of horizontal segments/line.  Enlarge this if you are trying
   to use a font that is too "curvy" for XDaliClock to cope with.
   This code was sent to me by Dan Wallach <c169-bg@auriga.berkeley.edu>.
   I'm highly opposed to ever using statically-sized arrays, but I don't
   really feel like hacking on this code enough to clean it up.
 */
#ifndef MAX_SEGS_PER_LINE
# define MAX_SEGS_PER_LINE 2
#endif

struct scanline {
  POS left[MAX_SEGS_PER_LINE], right[MAX_SEGS_PER_LINE];
};

struct frame {
  struct scanline scanlines [1]; /* scanlines are contiguous here */
};


/* The runtime settings (some initialized from system prefs, but changable.)
 */
struct render_state {
  byte current_frame; /* 0->10, 0->7 are animation and 8-10 are hold */
  int char_width, char_height, colon_width;
  struct frame *base_frames [12];	/* all digits */
  struct frame *orig_frames [8];	/* what was there */
  byte          orig_digits [8];	/* what was there */
  struct frame *current_frames [8];	/* current intermediate animation */
  struct frame *target_frames [8];	/* where we are going */
  byte          target_digits [8];	/* where we are going */
  struct frame *empty_frame;
  struct frame *empty_colon;
  byte time_mode;
  byte date_mode;
  byte force_refresh;
};


struct frame *
make_empty_frame (byte width, byte height);

struct frame *
copy_frame (struct dali_config *c, struct frame *from);

struct frame *
number_to_frame (unsigned char *bits, byte width, byte height);

int
pick_font_size (struct dali_config *c, unsigned int *w_ret, unsigned int *h_ret);

void
init_numbers (struct dali_config *c);

void
free_numbers (struct dali_config *c);

void sub32(unsigned *ahi, unsigned *alo, unsigned bhi, unsigned blo,
           unsigned chi, unsigned clo);

void
fill_target_digits (struct dali_config *c, struct timeval *time);

extern byte _digital_ff_left_shifts[];
extern byte _digital_ff_right_shifts[];

void
draw_horizontal_line_white(struct dali_config *c, byte x1, byte x2, byte *scanline);

void
draw_horizontal_line_black(struct dali_config *c, byte x1, byte x2, byte *scanline);


byte
draw_frame (struct dali_config *c, struct frame *frame, byte x, byte y, int colonic_p);

void draw_clock (struct dali_config *c);

void
start_sequence (struct dali_config *c, struct timeval *time, byte render);

void
one_step (struct dali_config *c,
          struct frame *orig_frame,
          struct frame *current_frame,
          struct frame *target_frame,
          byte current_frame_num);

void
tick_sequence (struct dali_config *c);

void
compute_left_offset (struct dali_config *c);

void
draw_clock (struct dali_config *c);

void
render_init (struct dali_config *c);

void
render_free (struct dali_config *c);

void
render_once (struct dali_config *c);

void
render_bitmap_size (struct dali_config *c, 
                    unsigned int *w_ret, unsigned int *h_ret,
                    unsigned int *w2_ret, unsigned int *h2_ret);

#endif
