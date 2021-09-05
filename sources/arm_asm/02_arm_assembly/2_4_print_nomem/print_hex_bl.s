.globl _start
_start:
  mov r0, r15
  bl print_hex
  mov r0, #0x68
  bl print_hex
end:
  b end

# print_hex は r0 に入っている値を hex で UART に出力する
print_hex:
  ldr r1, =0x101f1000 // UART
  mov r2, #8         // counter
# print '0x'    
  mov r3, #0x30
  str r3, [r1]
  mov r3, #0x78
  str r3, [r1]
print_hex_loop:
  mov r3, r0
  lsl r0, r0, #4  // deadbeaf -> eadbeaf0
  lsr r3, r3, #28 // deadbeaf -> 0000000d
  cmp r3, #0x0a 
  bge print_single_hex_alpha
# print_single_hex_digit:
  add r3, r3, #0x30
  str r3, [r1]
  b check_printed_all
print_single_hex_alpha:
  sub r3, r3, #0x0a
  add r3, r3, #0x41
  str r3, [r1]
check_printed_all:
  sub r2, r2, #1
  cmp r2, #0
  bgt print_hex_loop
# print newline
  mov r3, #0x0D
  str r3, [r1]
  mov r3, #0x0A
  str r3, [r1]
# return to the next line of print_hex call
  mov r15, r14
