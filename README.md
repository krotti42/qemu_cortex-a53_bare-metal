# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example

Minimal Cortex-A53 (ARMv8-A) bare-metal example which is running on QEMU.

## NOTES

* Low address startup at entry point `0x41000000`

On QEMU with the default machine `virt` the first 1GiB region is reserved for memory mapped devices. The next 16MiB starting at PMA `0x40000000` are for the DTB (device tree blob). Currently the DTB will not be parsed.
Therefore the entry `_lstart` starts at PA `0x41000000`. The low startup creates basic translation tables for the MMU and enables it. Then it jumps to the higher half kernel entry `_start`.

* Higher half kernel (entry point VMA `0xFFFF0000_41200000` mapped to PMA `0x41200000`)

The kernel currently only setups the stack pointer for itself, setups a basic interrupt vector table and enables them and zeros the `.bss` section for C runtime. Then for testing purpose it loops forever currently.

## Memory Map (QEMU)

Machine `virt` with default settings (2GiB):

| Physical Address (PMA) | Size                | Content                        |
|------------------------|---------------------|--------------------------------|
| 0x00000000_00000000    | 0x00000000_40000000 | Device memory                  |
| 0x00000000_40000000    | 0x00000000_01000000 | RAM reserved (16MiB for DTB)   |
| 0x00000000_41000000    | 0x00000000_7F000000 | RAM free usable (2GiB - 16MiB) |

Machine `virt` with 4GiB memory:

| Physical Address (PMA) | Size                | Content                        |
|------------------------|---------------------|--------------------------------|
| 0x00000000_00000000    | 0x00000000_40000000 | Device memory                  |
| 0x00000000_40000000    | 0x00000000_01000000 | RAM reserved (16MiB for DTB)   |
| 0x00000000_41000000    | 0x00000000_FF000000 | RAM free usable (4GiB - 16MiB) |

**NOTE:**  
Dump QEMU's DTB command:
```
$ qemu-system-aarch64 -m 4G -machine virt,dumpdtb=virt.dtb -cpu cortex-a53
```
Convert DTB to human readable DTS command with device tree compiler and view with `less`:
```
$ dtc -I dtb -O dts virt.dtb | less
```

## Virtual Memory Map (Kernel)

| Physical Address (PMA) | Virtual Address (VMA) | Content                   |
|------------------------|-----------------------|---------------------------|
| 0x00000000_00000000    | 0xFFFF0000_00000000   | Device memory (1GiB)      |
| 0x00000000_40000000    | 0xFFFF0000_40000000   | QEMU's DTB (16MiB)        |
| 0x00000000_41000000    | 0xFFFF0000_41000000   | Low kernel startup (2MiB) |
| 0x00000000_41200000    | 0xFFFF0000_41200000   | Kernel (256MiB)           |

**NOTE:**  
Current setup for `TTBR1_EL1`, is setup in low kernel startup currently.

## TODO

* Add basic userspace (EL0)
* Implement basic syscalls
* and many more...

## Prerequisites for building

* GCC and GNU binutils for `aarch64-none-elf` targets
* GNU make

## Building

```
$ cd src/kern
$ make
```

## Run on QEMU

```
$ qemu-system-aarch64 -m 4G -machine virt -cpu cortex-a53 -device loader,file=./kern.elf,cpu-num=0 -d in_asm,cpu
```

## Debug with GDB

* Start/Run `kern.elf` with option `-s -S`:
```
$ qemu-system-aarch64 -m 4G -machine virt -cpu cortex-a53 -s -S -device loader,file=./kern.elf,cpu-num=0 -d in_asm,cpu
```
* Start GDB with:
```
$ aarch64-none-elf-gdb ./kern.elf
```
* In GDB command line connect to QEMU:
```
(gdb) target remote localhost:1234
```
* Now we can setup breakpoints, use single steps and so soon.
