src_asm = [
  'system/src/boot.asm',
  'system/src/x86-64/ap_init.asm',
  'system/src/x86-64/cpu_functions.asm',
  'system/src/x86-64/enable_64bit.asm',
  'system/src/x86-64/init.asm',
  'system/src/x86-64/system_isr.asm'
]

res = run_command('compile_asm.sh', 
  meson.source_root(),
  meson.current_build_dir(), 
  src_asm
)
objs_asm = res.stdout().strip().split('\n')