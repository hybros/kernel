IMG    = test.img
ISO    = test.iso
KERNEL = kernel.bin
MODS   = memory-managers.bin

SRC = ../src
BIN = ../bin

CP = cp
RM = rm -f

#TY = tput setaf 3
#TR = tput sgr0

$(ISO):
	@#$(TY)
	@echo "Generating $(ISO)..."
	@#$(TR)
	cd ..; grub-mkrescue -o $(ISO) bin

img:
	@#$(TY)
	@echo "Generating $(IMG)..."
	@#$(TR)
	@cd ../bin; grub-mkimage -C auto -O i386-pc -o ../test.img multiboot fat
	
clean:
	$(RM) $(KERNEL) $(MODS)
	$(RM) ../$(ISO)
	
