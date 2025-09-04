# my very own assembly and CPU
this is my first bigger C projects so please be kind to me


right now, i am working on the assembler where I've already finished tokenization and basically I just need to translate it into binary


the compiler is really simple and the pipeline is like this:
```
code.asm -> tokenize lines into array -> remove comments from every line -> tokenize every line of the array and create matrix by that -> translating it into machine code (TODO) -> code.o
```

i'll make the CPU in the future

