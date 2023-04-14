clang-format -i *.c *.h

clang -O2 -std=c2x -Weverything ^
    -fsanitize=address ^
    bst_delete.c ^
    -o a.exe
a
del a.exp a.lib a.pdb a.exe
