# core and variant dirs for libraries (using arduino nano)
ARDUINOCOREDIR = $(ARDUINODIR)/hardware/arduino/avr/cores/arduino
VARIANTDIR = $(ARDUINODIR)/hardware/arduino/avr/variants/eightanaloginputs

# where to find the avr tools (using the ones from arduino)
AVRTOOLSDIR = $(ARDUINODIR)/hardware/tools/avr
AVR-GCC = $(AVRTOOLSDIR)/bin/avr-gcc
AVR-G++ = $(AVRTOOLSDIR)/bin/avr-g++
AVR-GCC-AR = $(AVRTOOLSDIR)/bin/avr-gcc-ar
AVR-OBJCOPY = $(AVRTOOLSDIR)/bin/avr-objcopy
AVRDUDE = $(AVRTOOLSDIR)/bin/avrdude

# where to place built objects (used for the completed sketch, the core and the libraries submakes)
OUTDIR = build
