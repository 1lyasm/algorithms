clang -O2 -Weverything -Werror ^
    -fsanitize=address -ansi ^
    construct_binary_tree.c ^
    test_construct_binary_tree.c ^
    -o a.exe
a
del a.exp a.lib a.pdb a.exe
