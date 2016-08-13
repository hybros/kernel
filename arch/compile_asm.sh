#!/bin/bash

ASM=nasm
FLAGS="-f elf64"

for src in "${@:3}"; do
  out=${src//['/','..']/_}.o
  ${ASM} ${FLAGS} $1/src/${src} -o $2/${out}
  echo $2/${out}
done