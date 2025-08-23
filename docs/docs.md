8 bit cpu

can handle 256 instructions

4 registers
r0 - null register
r1
r2
r3
r4

instruction set:
0x00 - null 
0x01 - add arg1 arg2 register
0x02 - sub arg1 arg2 register
0x03 - or arg1 arg2 register
0x04 - not arg vaccant register
0x05 - and arg1 arg2 register
0x06 - mul arg1 arg2 register
0x07 - div arg1 arg2 register
0x08 - je compare compare jump_to 
0x09 - jg compare compare jump_to 
0x10 - jl compare compare jump_to 
0x11 - jmp vacant vacant jump_to
0x08-0x14 is vaccant
0x15 - halt


flags:
0x00 - null
0x01 - 
TODO: finish architecture:
    give codes to the assembly tokens