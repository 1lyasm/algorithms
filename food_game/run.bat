clang -ansi -O2 -Weverything -fsanitize=address *.c -o a.exe
a
del *.exp *.lib *.pdb *.exe
