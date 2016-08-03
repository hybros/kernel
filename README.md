# HYBROS-Kernel 

## What is this?

This is C++14 x86/x86-64 kernel to explore new features and bring different ideas together.
E.g. I want to integrate a Garbage Collector and checkout if this could even make a kernel more secure.
This would also make it possible to write kernel code in modern high level languages like [Go](https://www.go-lang.org/) or [Crystal](https://www.crystal-lang.org/)
(BTW: my current favorite) beside what already is possible with [Rust](https://www.rust-lang.org/).

Another idea is to include Linux as a subkernel plus userspace so existing programs can be run on HYBROS.
In a much more far away future Windows may also run under HYBROS sharing its drivers and Windows-specific functionality with Linux and possibly others.

I know that this is a really big project so if you are interested in contributing to it, contact me.

## Current features

- 64 bit environment
- Memory managers (physical, virtual and heap)
- C++ std library implementations like string and vector but reinterpreted
- Beginning multhreading support
