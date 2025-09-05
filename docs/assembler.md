# Assembler
version: 0.1


This program compiles custom assembly into binary code, binary code is defined in instruction_set
## use: 
```
assembler <PATH/TO/YOUR/PROGRAM.ASM>
```
this outputs output.o which can be runable in custom assembly interpreter


# TODO:
- MAX_TOKENS and MAX_INSTRUCTION_LEN make as const and not preprocesor macro
- functions: naming file, able to print in hex, printing output while compiling
- R0 register
- Function statement (GOTO)