# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example

Minimal Cortex-A53 (ARMv8-A) bare-metal example which is running on QEMU.

## NOTES

* Low address startup at entry point `0x41000000`

On QEMU with the default machine `virt` the first 1GiB region is reserved for memory mapped devices. The next 16MiB starting at PA `0x40000000` are for the DTB (device tree blob). Currently the DTB will not be parsed.
Therefore the entry `_lstart` starts at PA `0x41000000`. The low startup creates basic translation tables for the MMU and enables it. The it jumps to the higher half kernel entry `_start`.

* Higher half kernel (entry point VMA `0xFFFF0000_80000000` mapped to PA `0x80000000`)

The kernel currently only setups the stack pointer for itself, setups a basic interrupt vector table and enables them and zeros the `.bss` section for C runtime. Then for testing purpose it loops forever currently.

## TODO

* Add basic userspace (EL0)
* Implement basic syscalls
* and many more...
