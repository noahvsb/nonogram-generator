# nonogram generator

A generator for nonogram puzzles, written in C (just to flex).
The output is a string that you can copy/paste into discord.

Doesn't check if the solution is unique yet, but that feature's coming soon.

## How to run

### Compile using any C compiler (like gcc)
examples:
```c
gcc nonogram.c -o nonogram
gcc nonogram.c -o nonogram.exe
gcc nonogram.c -o nonogram.o
```

### Execute
examples:
```c
nonogram.exe # windows
./nonogram.o # linux
```

### Arguments
You can pass on 4 optional arguments:

```c
nonogram -d 3 -c 0.5 --fill :thumbs_up: --unfill :thumbs_down:

-d n | --dim n: dimension of nonogram (default = 5)
-c p | --chance p: chance of nonogram square being filled (default = 0.6)
--fill EMOJI: discord emoji of filled square (default = :large_black_square:)
--unfill EMOJI: discord emoji of unfilled square (default = :large_white_square:)
