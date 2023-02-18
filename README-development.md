## Coding conventions

Use tabs for indentation, however try to minimize changes and don't re-format lines that aren't part of your task. The project has a long history and when most of the code was created, there were many authors but no coding conventions.

## Building

Compiling:
```
make
```

Running tests:
```
make test
```

It is recommended that you install Valgrind and run tests using it (as it is done in Travis CI):
```
./test.pl --valgrind
```

Also recommended: check if compilation is not broken on oldest compilers supported by Tex Live (again, if you don't do this, it will be checked on CI):
```
make clean all DEFS='-std=iso9899:199409'
```
