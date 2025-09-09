# LArch8
Lukas's Architecture 8 bit
## my very own assembly and CPU Interpreter
This is my first bigger C projects so please be kind to me


## Assembler

the assembler is really simple and the pipeline is like this:
```
code.asm -> tokenize lines into array -> remove comments from every line -> tokenize every line of the array and create matrix by that -> translating it into machine code -> code.o
```

## Interpreter
even simpler
```
code.o -> parsing -> header check -> runtime
```

