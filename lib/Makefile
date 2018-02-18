include ../arduinoenvironment.mk

# library objects to compile
SOURCES = \
	  TM1638/InvertedTM1638.cpp \
	  TM1638/TM1638.cpp \
	  TM1638/TM1638QYF.cpp \
	  TM1638/TM1640.cpp \
	  TM1638/TM16XX.cpp \
	  OneWire/OneWire.cpp

OBJECTS = $(patsubst %, $(OUTDIR)/%.o, $(SOURCES))

# pack all library objects together so they can be easily linked from the base
# makefile without knowing the exact object names
$(OUTDIR)/libs.a: $(OBJECTS)
	$(AVR-GCC-AR) rcs $@ $(OBJECTS)

# note that the options are different for libraries than for the sketch objects
$(OUTDIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(AVR-G++) -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10803 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   "-I$(ARDUINOCOREDIR)" "-I$(VARIANTDIR)" -I$(dir $<) "$<" -o "$@"

# TODO XXX FIXME: add support for .s and .c library files compilation

.PHONY: clean
clean:
	rm -rf $(OUTDIR)/*
