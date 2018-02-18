# where the arduino is connected (for flashing)
PORT=/dev/ttyUSB0

# where to find the cores code and variant code
ARDUINODIR = $(HOME)/arduino-1.8.3
AVRTOOLSDIR = $(ARDUINODIR)/hardware/tools/avr
ARDUINOCOREDIR = $(ARDUINODIR)/hardware/arduino/avr/cores/arduino
VARIANTDIR = $(ARDUINODIR)/hardware/arduino/avr/variants/eightanaloginputs

# where to find the avr tools
AVR-GCC = $(AVRTOOLSDIR)/bin/avr-gcc
AVR-G++ = $(AVRTOOLSDIR)/bin/avr-g++
AVR-GCC-AR = $(AVRTOOLSDIR)/bin/avr-gcc-ar
AVR-OBJCOPY = $(AVRTOOLSDIR)/bin/avr-objcopy
AVRDUDE = $(AVRTOOLSDIR)/bin/avrdude

# where to place built objects (used for the completed sketch, the core and the libraries submakes)
OUTDIR = build
