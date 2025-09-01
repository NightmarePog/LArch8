TODO:
- not enough space for 32 bits because i need 41 bits per one instruction:
8 - OP CODE
8 - value + 3 type
8 - value + 3 type
8 - value + 3 type


ver 2:
4 - OP CODE
8 - value + 2 type
8 - value + 2 type
8 - value + 2 type
=
34
still need 2 more bits -w-
currect arc


this is gonna be pain i might need to rework it -w-
solutions? 
- make it smaller
- make instruction buffer to 64 bit (probably million times easier)