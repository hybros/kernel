CC = g++
AS = nasm
RM = rm -f
LD = ld

#TY = tput setaf 3
#TR = tput sgr0

override AFLAGS  += -f elf64
override CFLAGS  += -m64 -mcmodel=kernel -mno-red-zone -nostdlib -nostdinc -ffreestanding -fvisibility=hidden -O2 -Wall -Wextra -fno-exceptions -fno-rtti -std=c++0x -c
override LDFLAGS += -z max-page-size=0x1000 -T link.ld -Bsymbolic -L:../../../../bin/boot/kernel.bin

CSRCS = main.cpp \
	   hmm_bitmap.cpp \
	   pmm_bitmap.cpp

COBJS = $(CSRCS:.cpp=.o)
CHDRS = $(CSCRS:.cpp=.hpp)

AOBJS = $(ASRCS:.asm=.o)

OUTPUT = memory-managers.bin

.SUFFIXES: .cpp .o .hpp .asm

$(OUTPUT): $(COBJS) $(AOBJS)
	@#$(TY)
	@echo "$(OUTPUT): Linking $@ to binary..."
	@#$(TR)
	$(LD) $(LDFLAGS) $(COBJS) $(AOBJS) -o $(OUTPUT)
	@#$(TY)
	@echo "$(OUTPUT): Moving $(OUTPUT) binary to \"bin\" directory..."
	@#$(TR)
	@mv $(OUTPUT) ../../../../bin/boot/modules/$(OUTPUT)

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
