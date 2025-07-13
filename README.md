# nonogram generator

A generator for nonogram puzzles, written in C (just to flex).
The output is a string that you can copy/paste into discord.

Doesn't check if the solution is unique yet, but that feature's coming soon.

## How to run

### Compile using any C compiler (like gcc)
examples:
```sh
gcc nonogram.c -o nonogram
gcc nonogram.c -o nonogram.exe
gcc nonogram.c -o nonogram.o
```

### Execute
examples:
```sh
nonogram.exe # windows
./nonogram.o # linux
```

### Arguments
You can pass on 2 optional arguments.

First argument is the dimension (default = 5)

Second argument is the chance for a square to be white (default = 0.6)

```sh
nonogram 3 0.5
```
