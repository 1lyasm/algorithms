clang -O2 -fsanitize=address main.c -o a.exe
a
del *.exe *.pdb *.lib *.exp