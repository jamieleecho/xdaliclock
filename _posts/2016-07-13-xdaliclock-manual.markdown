---
layout: post
title:  "xdaliclock Manual"
date:   2016-07-13 08:29:56 -0500
categories: xdaliclock manual coco
---
## xdaliclock
[![Download]({{site.url}}{{site.baseurl}}/assets/Images/Download.png)](https://github.com/jamieleecho/xdaliclock/releases/download/v0.1.0/xdali.dsk)

({{site.url}}{{site.baseurl}}/assets/2015-12-12/Images/GameAction.png)
xdaliclock is a [Tandy/TRS-80 Color
Computer](https://en.wikipedia.org/wiki/TRS-80_Color_Computer) port of [Jamie
Zawinski's](https://www.jwz.org/)
[xdaliclock](https://www.jwz.org/xdaliclock/). xdaliclock is a digital clock
whose digits "melt" when they change value.


## Requirements
xdaliclock requires the following:

* A Tandy/TRS-80 Color Computer or emulator with at least 32K or more RAM
* A Floppy Disk Drive such as the FD-501 or emulator such as the CoCo SDC


## Getting Started
xdaliclock is supplied on a disk image that is compatible with most Color
Computer emulators. To use this clock, you must transfer the disk image to a
physical floppy disk or transfer it to a system such as
[DriveWire](https://sites.google.com/site/drivewire4/) or the [CoCo
SDC](http://cocosdc.blogspot.com). Please refer to the appropriate system
manual for inserting the game disk or image into your system.

Turn on your computer or emulator and insert the disk or image into the system.
Type the following at the OK prompt and press the **\[Enter\]** key.

~~~~~~
RUN "*"
~~~~~~

xdaliclock will loadi When prompted, enter the year (2016->9999), month
(1->12), day (1->31), hour (0->23), minute (0->59) and second (0->59).  ![Enter
Date and Time
Screen]({{site.url}}{{site.baseurl}}/assets/2016-07-13/Images/enter_date_time.png)

xdaliclock will now show its title screen.  ![Main
Screen]({{site.url}}{{site.baseurl}}/assets/2016-07-13/Images/main.png)


## Running xdaliclock
* Press \[spacebar\] to momentarily switch from time mode to date mode.

* Pressing \[1\] will display the current hour, minute and second in time mode.
  In date mode it will display the year, month and day of month.

* Pressing \[2\] will display the current hour and minute in time mode. In date
  mode it will display the month and day of month.

* Pressing \[3\] will display the current second in time mode. In date mode it
  will display the day of month.

* Pressing \[4\] will display the date as MM-DD-YY in date mode.

* Pressing \[5\] will display the date as DD-MM-YY in date mode.

* Pressing \[6\] will display the date as YY-MM-DD in date mode.


## Bugs
* This program will allow entering a bogus date such as 2/31

* This program is based on the Color Computer BASIC clock which is not the most
  accurate time keeper around.


## Acknowledgements
Thanks to Steve Capps for developing the original Dali Clock and Jamie Zawinski
for developing xdaliclock on which this is based.  I thank Pierre Sarrazin for
developing and maintaining the
[CMOC](http://perso.b2b2c.ca/~sarrazip/dev/cmoc.html) compiler that was used to
develop xdaliclock.
