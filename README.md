# LArch8

LArch8 is an early C learning project that explores a small 8-bit architecture,
an assembler, and a CPU interpreter.

> **Status:** Learning project. It represents an early experiment rather than a
> production-ready toolchain.

## Assembler

The assembler translates a source file into the bytecode consumed by the
interpreter:

```
code.asm -> tokenize lines -> remove comments -> parse instructions -> code.o
```

## Interpreter

The interpreter validates the object-file header and executes the encoded
instructions:

```
code.o -> parse -> validate header -> execute
```
