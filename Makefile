include arduinoenvironment.mk
SRCDIR = src
LIBDIR = lib
COREDIR = arduinocore

SOURCES = $(SRCDIR)/main.cpp \
          $(SRCDIR)/devices/DS18x20.cpp \
          $(SRCDIR)/devices/LedKey.cpp

OBJECTS = $(patsubst $(SRCDIR)/%, $(OUTDIR)/%.o, $(SOURCES))

G++INCLUDES = $(patsubst %, -I%, $(wildcard $(LIBDIR)/*))

ELF = $(OUTDIR)/main.elf
EEP = $(OUTDIR)/main.eep
HEX = $(OUTDIR)/main.hex

# linking everything together
# (the hex depends on the sketch objects, the libs and the arduino core)
$(HEX): $(OBJECTS) $(LIBDIR)/$(OUTDIR)/libs.a $(COREDIR)/$(OUTDIR)/core.a
	$(AVR-GCC) -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -o "$(ELF)" $(OBJECTS) "$(LIBDIR)/$(OUTDIR)/libs.a" "$(COREDIR)/$(OUTDIR)/core.a" -lm
	$(AVR-OBJCOPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "$(ELF)" "$(EEP)"
	$(AVR-OBJCOPY) -O ihex -R .eeprom  "$(ELF)" "$(HEX)"

# compiling sketch
.PHONY: sketch
sketch: $(OBJECTS)

$(OUTDIR)/%.cpp.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(AVR-G++) -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10803 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR "-I$(ARDUINOCOREDIR)" "-I$(VARIANTDIR)" "-I$(SRCDIR)" $(G++INCLUDES) "$<" -o "$@"

# compiling core
.PHONY: core
core: $(COREDIR)/$(OUTDIR)/core.a
$(COREDIR)/$(OUTDIR)/core.a:
	cd $(COREDIR) && $(MAKE)

# compiling libraries
.PHONY: libs
libs: $(LIBDIR)/$(OUTDIR)/libs.a
$(LIBDIR)/$(OUTDIR)/libs.a:
	cd $(LIBDIR) && $(MAKE)

# flash the sketch into a real arduino
.PHONY: flash
flash: $(HEX)
	$(AVRDUDE) -C$(AVRTOOLSDIR)/etc/avrdude.conf -v -patmega328p -carduino -P$(PORT) -b57600 -D -Uflash:w:$(HEX):i

# clean up sketch and completed linked objects
.PHONY: clean
clean:
	rm -rf $(OUTDIR)/*

# clean up also built core and libraries
.PHONY: mrproper
mrproper: clean
	cd $(COREDIR) && $(MAKE) clean
	cd $(LIBDIR) && $(MAKE) clean
