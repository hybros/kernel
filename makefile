ISO = test.iso

#UNAME_P := $(shell uname -p)
	
ARCH := x86_64
	
.phony: clean
	
$(ISO):
ifeq ($(ARCH), x86_64)
	cd src/kernel/build/x86-64; make
	cd build;		    make
endif
ifeq ($(ARCH), x86)
	cd src/kernel/build/x86;    make
endif
ifeq ($(ARCH), arm)
	cd src/kernel/build/arm;    make
endif
		
clean:
ifeq ($(ARCH), x86_64)
	cd src/kernel/build/x86-64; make clean
	cd build;		    make clean
endif
ifeq ($(ARCH), x86)
	cd src/kernel/build/x86;    make clean
endif
ifeq ($(ARCH), arm)
	cd src/kernel/build/arm;    make clean
endif
