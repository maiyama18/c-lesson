/*
 arm-none-eabi-as print_hex.s -o print_hex.o
 arm-none-eabi-ld print_hex.o -Ttext 0x00010000 -o print_hex.elf
 arm-none-eabi-objcopy print_hex.elf -O binary print_hex.bin
 qemu-system-arm -M versatilepb -m 128M -nographic -kernel print_hex.bin -serial mon:stdio
*/
.globl _start
_start:
    ldr r0,=0x101f1000
    ldr r1,=0xdeadbeaf
    mov r8, #8 // counter
print_hex:
    mov r2, r1
    lsl r1, r1, #4 // deadbeaf -> eadbeaf0
    lsr r2, r2, #28 // deadbeaf -> 0000000d
    cmp r2, #0x0a 
    bge print_single_hex_alpha
// print_single_hex_digit:
    add r2, r2, #0x30
    str r2, [r0]
    b check_printed_all
print_single_hex_alpha:
    sub r2, r2, #0x0a
    add r2, r2, #0x41
    str r2, [r0]
check_printed_all:
    sub r8, r8, #1
    cmp r8, #0
    bgt print_hex
end:
    b end
