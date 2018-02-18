include ../arduinoenvironment.mk

# probably all the sources in arduinocoredir, manually listed to control what
# is built and avoid future errors
SOURCES = \
	  $(ARDUINOCOREDIR)/wiring_pulse.S \
	  $(ARDUINOCOREDIR)/WInterrupts.c \
	  $(ARDUINOCOREDIR)/hooks.c \
	  $(ARDUINOCOREDIR)/wiring.c \
	  $(ARDUINOCOREDIR)/wiring_analog.c \
	  $(ARDUINOCOREDIR)/wiring_digital.c \
	  $(ARDUINOCOREDIR)/wiring_pulse.c \
	  $(ARDUINOCOREDIR)/wiring_shift.c \
	  $(ARDUINOCOREDIR)/CDC.cpp \
	  $(ARDUINOCOREDIR)/HardwareSerial.cpp \
	  $(ARDUINOCOREDIR)/HardwareSerial0.cpp \
	  $(ARDUINOCOREDIR)/HardwareSerial1.cpp \
	  $(ARDUINOCOREDIR)/HardwareSerial2.cpp \
	  $(ARDUINOCOREDIR)/HardwareSerial3.cpp \
	  $(ARDUINOCOREDIR)/IPAddress.cpp \
	  $(ARDUINOCOREDIR)/PluggableUSB.cpp \
	  $(ARDUINOCOREDIR)/Print.cpp \
	  $(ARDUINOCOREDIR)/Stream.cpp \
	  $(ARDUINOCOREDIR)/Tone.cpp \
	  $(ARDUINOCOREDIR)/USBCore.cpp \
	  $(ARDUINOCOREDIR)/WMath.cpp \
	  $(ARDUINOCOREDIR)/WString.cpp \
	  $(ARDUINOCOREDIR)/abi.cpp \
	  $(ARDUINOCOREDIR)/main.cpp \
	  $(ARDUINOCOREDIR)/new.cpp

OBJECTS = $(patsubst $(ARDUINOCOREDIR)/%, $(OUTDIR)/%.o, $(SOURCES))

# pack all core objects together so they can be easily linked from the base
# makefile without knowing the exact names
$(OUTDIR)/core.a: $(OBJECTS)
	$(AVR-GCC-AR) rcs  "$@" $(OBJECTS)

$(OUTDIR)/%.S.o: $(ARDUINOCOREDIR)/%.S
	$(AVR-GCC) -c -g -x assembler-with-cpp -flto -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10803 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   "-I$(ARDUINOCOREDIR)" "-I$(VARIANTDIR)" "$<" -o "$@"

$(OUTDIR)/%.cpp.o: $(ARDUINOCOREDIR)/%.cpp
	$(AVR-G++) -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10803 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   "-I$(ARDUINOCOREDIR)" "-I$(VARIANTDIR)" "$<" -o "$@"

$(OUTDIR)/%.c.o: $(ARDUINOCOREDIR)/%.c
	$(AVR-GCC) -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10803 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   "-I$(ARDUINOCOREDIR)" "-I$(VARIANTDIR)" "$<" -o "$@"

.PHONY: clean
clean:
	rm -rf $(OUTDIR)/*
