CFLAGS=-O2 -I../font
LDFLAGS=--org=0x2a00 --limit=0x7fff
TARGET=xdali.dsk
TARGET_BAS=$(TARGET:.dsk=.bas)
TARGET_BIN=$(TARGET:.dsk=.bin)
TARGET_C=$(TARGET:.dsk=.c)
TEST_TARGET=test.dsk

MESS_DIR=~/Applications/mame
MESS=$(MESS_DIR)/mame64

C_SOURCES=$(wildcard *.c)
C_OBJS=$(patsubst %.c,%.o,$(C_SOURCES))

$(TARGET) : $(TARGET_BAS) $(TARGET_BIN)
	rm -f $@
	decb dskini $@
	decb copy $(TARGET_BAS) $@,"*.BAS" -t
	decb attr $@,"*.BAS" -0
	decb copy $(TARGET_BAS) $@,$(shell echo $(TARGET_BAS) | tr a-z A-Z) -t
	decb attr $@,$(shell echo $(TARGET_BAS) | tr a-z A-Z) -0
	decb copy $(TARGET_BIN) $@,$(shell echo $(TARGET_BIN) | tr a-z A-Z)
	decb attr $@,$(shell echo $(TARGET_BIN) | tr a-z A-Z) -2 -b

$(TEST_TARGET) : $(TARGET_BAS) testuint.bin testfp.bin testmem.bin \
                 testtstr.bin
	rm -f $@
	decb dskini $@
	decb copy $(TARGET_BAS) $@,"*.BAS" -t
	decb attr $@,"*.BAS" -0
	decb copy $(TARGET_BAS) $@,$(shell echo $(TARGET_BAS) | tr a-z A-Z) -t
	decb attr $@,$(shell echo $(TARGET_BAS) | tr a-z A-Z) -0
	decb copy testuint.bin $@,TESTUINT.BIN
	decb attr $@,TESTUINT.BIN -2 -b
	decb copy testfp.bin $@,TESTFP.BIN
	decb attr $@,TESTFP.BIN -2 -b
	decb copy testmem.bin $@,TESTMEM.BIN
	decb attr $@,TESTMEM.BIN -2 -b
	decb copy testtstr.bin $@,TESTTSTR.BIN
	decb attr $@,TESTTSTR.BIN -2 -b

all : $(TARGET) $(TEST_TARGET)


testuint.bin: testuint.o c_stuff.o tester.o setjmp.o UInt32.o
	cmoc $(CFLAGS) $(LDFLAGS) $^

testfp.bin: testfp.o c_stuff.o tester.o setjmp.o FixedPoint.o
	cmoc $(CFLAGS) $(LDFLAGS) $^

testtstr.bin: testtstr.o c_stuff.o tester.o setjmp.o
	cmoc $(CFLAGS) $(LDFLAGS) $^

testmem.bin: testmem.o c_stuff.o tester.o setjmp.o
	cmoc $(CFLAGS) $(LDFLAGS) $^


$(TARGET_BIN) : $(filter-out FixedPoint.o tester.o testuint.o testfp.o testtstr.o testmem.o, $(C_OBJS))
	cmoc $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o : %.c
	cmoc $(CFLAGS) -c $<

clean :
	rm -rf $(TARGET) $(TEST_TARGET) $(C_OBJS) $(TARGET_BIN) testuint.bin testfp.bin testtstr.bin testmem.bin *.i *.lst *.asm *.hex *.link *.s *.map

run : $(TARGET)
	$(MESS) coco3 -rompath $(MESS_DIR)/roms -window -flop1 $(TARGET) -cfg_directory ../cfgs/rgb

test : $(TEST_TARGET)
	$(MESS) coco3 -rompath $(MESS_DIR)/roms -window -flop1 $(TEST_TARGET) -cfg_directory ../cfgs/rgb

run_cmp : $(TARGET)
	$(MESS) coco3 -rompath $(MESS_DIR)/roms -window -flop1 $(TARGET) -cfg_directory ../cfgs/cmp

debug : $(TARGET)
	$(MESS) coco3 -rompath $(MESS_DIR)/roms -window -flop1 $(TARGET) -cfg_directory ../cfgs/rgb -debug

debug_cmp : $(TARGET)
	$(MESS) coco3 -rompath $(MESS_DIR)/roms -window -flop1 $(TARGET) -cfg_directory ../cfgs/cmp -debug


