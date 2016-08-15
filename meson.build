subdir('arch')

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
  'system/src/x86-64/system_vmm.cpp'
]

src_std = [
  'hstd/src/memory.cpp',
  'hstd/src/string.cpp',
  'hstd/src/bitfield.cpp',
  'hstd/src/reference_counter.cpp',
  'hstd/src/x86-64/bits.cpp',
  'hstd/src/x86-64/exception.cpp'
]

kernel = executable('kernel', 
  src_sys, src_std, objs_asm,
  cpp_args : [
    '--target=x86_64-pc-none-elf',
    '-march=x86-64',
    '-m64', 
    '-mcmodel=large', 
    '-mno-red-zone', 
    '-nostdlib', 
    '-nostdinc', 
    '-ffreestanding',
    '-fvisibility=hidden', 
    '-O2', 
    '-Wall', 
    '-Wextra', 
    '-fno-exceptions',
    '-fno-rtti', 
    '-fno-builtin'
  ], 
  link_args : [
    '-z', 'max-page-size=0x1000',
    '-T', meson.source_root() + '/src/build/x86-64/link.ld'
  ],
  include_directories : include_directories('public')
)