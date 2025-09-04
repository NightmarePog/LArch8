TODO:
- not enough space for 32 bits because i need 41 bits per one instruction:
8 - OP CODE
8 - value + 3 type
8 - value + 3 type
8 - value + 3 type

example INSTRUCTION: 000F000E07FA000E
DEFINED AS: 
- 000F - ADD
- 000E - R3
- 07FA - [255]
- 000E - R3


# TODO:
MAX_TOKENS and MAX_INSTRUCTION_LEN make as const and not preprocesor macro