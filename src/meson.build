subdir('build')

src_sys = [
  'system/src/icxxabi.cpp',
  'system/src/main.cpp',
  'system/src/system.cpp',
  'system/src/system_asm.cpp',
  'system/src/system_internal.cpp',
  'system/src/system_manager.cpp',
  'system/src/system_pmm.cpp',
  'system/src/system_hmm.cpp',
  'system/src/system_terminal.cpp',
  'system/src/x86-64/system.cpp',
  'system/src/x86-64/system_vmm.cpp',
  'system/src/x86-64/system_int_manager.cpp'
]

inc_sys = 'system'

src_proc = [
  'processor/src/local_apic.cpp',
  'processor/src/x86-64/idt.cpp'
]

inc_proc = 'processor'

src_std = [
  'hstd/src/memory.cpp',
  'hstd/src/string.cpp',
  'hstd/src/bitfield.cpp',
  'hstd/src/reference_counter.cpp',
  'hstd/src/x86-64/bits.cpp',
  'hstd/src/x86-64/exception.cpp'
]

inc_std = 'hstd'
inc_vis = 'visual'
inc_mem = 'memory'

inc_dirs = include_directories(inc_sys, inc_proc, inc_mem, inc_std, inc_vis)
kernel = executable('kernel', 
  src_sys, src_proc, src_std, 
  objects : objs_asm,
  cpp_args : [
    '-m64', '-mcmodel=large', '-mno-red-zone', '-nostdlib', '-nostdinc', '-ffreestanding',
    '-fvisibility=hidden', '-O2', '-finline-functions', '-Wall', '-Wextra', '-fno-exceptions',
    '-fno-rtti', '-nostartfiles'
  ], 
  link_args : [
    '-z', 'max-page-size=0x1000',
    '-T', meson.source_root() + '/src/build/x86-64/link.ld'
  ],
  include_directories : inc_dirs
)