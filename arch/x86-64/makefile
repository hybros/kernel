CC = g++		#x86_64-elf-g++
AS = nasm
RM = rm -f
LD = ld			#x86_64-elf-ld

#TY = tput setaf 3 -mcmodel=kernel
#TR = tput sgr0

INC_SYS = -I../../system/
INC_STD = -I../../hstd/
INC_MEM = -I../../memory/
INC_VIS = -I../../visual/
INC_PROC = -I../../processor/
INC_MODS = -I../../modules/

INC_PATHS = $(INC_SYS) $(INC_STD) $(INC_MEM) $(INC_VIS) $(INC_PROC) $(INC_MODS)

override AFLAGS  += -f elf64
override CFLAGS  += -m64 -mcmodel=kernel -mno-red-zone -nostdlib -nostdinc -ffreestanding -fvisibility=hidden -O2 -finline-functions -Wall -Wextra -fno-exceptions -fno-rtti -std=c++11 $(INC_PATHS) -g -c
override LDFLAGS += -z max-page-size=0x1000 -T link.ld

CSRCS_SYS = \
	../../system/src/icxxabi.cpp \
	../../system/src/main.cpp \
	../../system/src/system.cpp \
	../../system/src/system_asm.cpp \
	../../system/src/system_internal.cpp \
	../../system/src/system_manager.cpp \
	../../system/src/system_pmm.cpp \
	../../system/src/system_hmm.cpp \
	../../system/src/system_terminal.cpp \
	../../system/src/x86-64/system.cpp \
	../../system/src/x86-64/system_vmm.cpp \
	../../system/src/x86-64/system_int_manager.cpp

CSRCS_PROC = \
	../../processor/src/local_apic.cpp \
	../../processor/src/x86-64/idt.cpp

CSRCS_STD = \
	../../hstd/src/memory.cpp \
	../../hstd/src/string.cpp \
	../../hstd/src/bitfield.cpp \
	../../hstd/src/reference_counter.cpp \
	../../hstd/src/x86-64/bits.cpp \
	../../hstd/src/x86-64/exception.cpp

CSRCS = $(CSRCS_STD) $(CSRCS_SYS) $(CSRCS_PROC)

ASRCS_SYS = \
	../../system/src/boot.asm \
	../../system/src/x86-64/enable_64bit.asm \
	../../system/src/x86-64/cpu_functions.asm \
	../../system/src/x86-64/init.asm \
	../../system/src/x86-64/ap_init.asm \
	../../system/src/x86-64/system_isr.asm

ASRCS_STD = ../../hstd/src/x86-64/memory.asm

ASRCS = $(ASRCS_SYS) $(ASRCS_STD)

COBJS = $(CSRCS:.cpp=.o)
CHDRS = $(CSCRS:.cpp=.hpp)

AOBJS = $(ASRCS:.asm=.o)

OUTPUT = hybros-kernel.elf

.SUFFIXES: .cpp .o .hpp .asm

$(OUTPUT): $(COBJS) $(AOBJS)
	@#$(TY)
	@echo "$(OUTPUT): Linking $@ to binary..."
	@#$(TR)
	$(LD) $(LDFLAGS) $(COBJS) $(AOBJS) -o $(OUTPUT)
	@#$(TY)
	@echo "$(OUTPUT): Moving $(OUTPUT) binary to \"bin\" directory..."
	@#$(TR)
	@mv $(OUTPUT) ../../../../bin/$(OUTPUT)

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

