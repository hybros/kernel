AC_PREREQ([2.69])
AC_INIT([HYBROS], [0.1], [hyronx@outlook.com])
AC_CONFIG_SRCDIR([src/kernel/system/src/system.cpp])
AC_CONFIG_HEADERS([src/kernel/hstd/include/bitmap.hpp])

AC_PROG_CXX
AC_CHECK_PROG([HAVE_NASM], [nasm], true, false)
AC_CHECK_PROG([HAVE_GRUB_TOOLS], [grub-mkrescue], true, false)

AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

srcdir = src


#AC_CONFIG_FILES([src/kernel/build/x86-64/makefile
#                 src/kernel/build/x86/makefile
#                 src/kernel/modules/memory-managers/makefile])
AC_OUTPUT
