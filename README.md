# xdaliclock
This version of xdaliclock is a port of [Jamie Zawinski's](https://www.jwz.org/) [xdaliclock](https://www.jwz.org/xdaliclock/) to the Tandy/TRS-80 [Color Computer](https://en.wikipedia.org/wiki/TRS-80_Color_Computer).

## Features
* Digital clock that morphs digits into their new shape when they change.
* Works on any Color Computer with a disk drive and 32KB RAM.
* Automatically runs at 1.78MHz on the Color Computer 3.

## Running xdaliclock
* Insert the disk or virtual disk into `DRIVE 0`.
* `RUN "*"`
* When prompted, enter the year (2016->9999), month (1->12), day (1->31), hour (0->23), minute (0->59) and second (0->59).
* Different time/date formats can be selected by pressing 1, 2 or 3.
* Different date formatting can be selected by pressing 4, 5 or 6.
* The date can be displayed momentarily by pressing the spacebar.

## Building xdaliclock
### Requirements
* Unix-like system such as Linux or macOS with typical developer tools
* [CMOC](http://perso.b2b2c.ca/~sarrazip/dev/cmoc.html)
* [LWTOOLS](http://lwtools.projects.l-w.ca)
* [MESS] (http://www.mess.org) and required coco roms

### Building and Running
```
cd xdaliclock/coco
make build
```