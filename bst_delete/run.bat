clang-format -i bst_delete.cpp
clang-format -i bst_delete_recursive.cpp
clang-format -i bst_delete.h

clang++ -O2 -std=c++2b -Weverything ^
    -fsanitize=address ^
    bst_delete.cpp ^
    bst_delete_recursive.cpp ^
    -o a.exe
a
del a.exp a.lib a.pdb a.exe
