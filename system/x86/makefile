CC = g++
AS = nasm
RM = rm -f
LD = ld

#TY = tput setaf 3
#TR = tput sgr0

INCSHARE  = ../../share
INCKSTD   = ../../kstd
INCFISYS  = ../../fisys
AFLAGS    = -f elf32
CFLAGS    = -m32 -nostdlib -nostdinc -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -std=c++0x -c
LDFLAGS   = -m elf_i386 -T link.ld

CSRCS = ../main.cpp \
	   ../system.cpp \
	   ../terminal.cpp \
	   $(INCKSTD)/icxxabi.cpp \
	   $(INCKSTD)/math.cpp \
	   $(INCKSTD)/string.cpp \
	   $(INCKSTD)/memory.cpp

ASRCS = ../entry.asm

COBJS = $(CSRCS:.cpp=.o)
CHDRS = $(CSCRS:.cpp=.hpp) 

AOBJS = $(ASRCS:.asm=.o)

OUTPUT = kernel.bin

.SUFFIXES: .cpp .o .hpp .asm

$(OUTPUT): $(COBJS) $(AOBJS)
	@#$(TY)
	@echo "$(OUTPUT): Linking $@ to binary..."
	@#$(TR)
	$(LD) $(LDFLAGS) $(COBJS) $(AOBJS) -o $(OUTPUT)
	@#$(TY)
	@echo "$(OUTPUT): Moving $(OUTPUT) binary to \"bin\" directory..."
	@#$(TR)
	@mv $(OUTPUT) ../../../bin/boot/$(OUTPUT)

.cpp.o: $(CHDRS)
	@#$(TY)
	@echo "$(OUTPUT): Compiling $@..."
	@#$(TR)
	$(CC) $(CFLAGS) $< -o $@

.asm.o:
	@#$(TY)
	@echo "$(OUTPUT): Compiling $@..."
	@#$(TR)
	$(AS) $(AFLAGS) $< -o $@

clean:
	@#$(TY)
	@echo "$(OUTPUT): Cleaning up $@..."
	@#$(TR)
	$(RM) $(COBJS) $(AOBJS)

