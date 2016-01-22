CC = g++
AS = yasm
RM = rm -f
LD = ld

#TY = tput setaf 3 -mcmodel=kernel
#TR = tput sgr0

override AFLAGS  += -f elf64
override CFLAGS  += -m64 -mno-red-zone -fPIC -nostdlib -nostdinc -ffreestanding -fvisibility=hidden -O2 -Wall -Wextra -fno-exceptions -fno-rtti -std=c++0x -c
override LDFLAGS += -z max-page-size=0x1000 -T link.ld

CSRCS_SYS = ../icxxabi.cpp \
		  ../system.cpp \
		  ../main.cpp \
		  ../terminal.cpp \
		  ../access_ctrl.cpp \
		  ../error_handler.cpp \
		  ../proc_ctrl.cpp \
		  ../pmms.cpp \
		  ../vmms.cpp

CSRCS_MEM = ../../memory/pmm_standard.cpp \
		  ../../memory/x86-64/vmm_standard.cpp

CSRCS_PROC = ../../processor/local_apic.cpp \
		   ../../processor/ipi.cpp

CSRCS_STD = ../../std/memory.cpp \
		  ../../std/string.cpp

CSRCS = $(CSRCS_STD) $(CSRCS_MEM) $(CSRCS_PROC) $(CSRCS_SYS)

ASRCS_SYS = ../boot.asm \
		  enable_64bit.asm \
		  cpu_functions.asm \
		  init.asm

ASRCS_STD = ../../std/x86-64/memory.asm

ASRCS = $(ASRCS_SYS) $(ASRCS_STD)

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
	@mv $(OUTPUT) ../../../../bin/boot/$(OUTPUT)

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

