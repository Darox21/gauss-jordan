# Gauss-Jordan Elimination
[![License](https://img.shields.io/badge/license-MIT%2FApache-blue.svg)](https://github.com/Darox21/gauss-jordan#LICENSE)

An implementation in C for the Gauss-Jordan Elimination algorithm for matrices of **fractions**.

The program receives a number of rows, a number of columns and the matrix data, for example:

```text
3 6
2 1/2 1 6 4 5
0 2 2/3 3 -1 5
1 0 1 3 3 2
```

```4 4
1 1 0 2
-2 -2 1 -5
1 1 -1 3
4 4 -1 9
```

The two files `gaussjordaner.c` and `gaussjordaner-step-by-step.c` perform the same algorithm but the step by step version prints each step as it calculates it along with a prettier formatting.

## Compilation

A `C` compiler is necessary to compile it; `gcc` is a good option, for it, install [MinGW for windows](https://sourceforge.net/projects/mingw/) or find the package for your linux distribution (with `apt-get gcc` or whatever).

The fraction library functions are defined in the file `frac.c` so it has to be included during compilation in the form:

```bash
gcc -o gaussjordaner gaussjordaner.c frac.c
```

Or on windows

```bash
gcc -o gaussjordaner.exe gaussjordaner.c frac.c
```
