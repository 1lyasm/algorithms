clang -O2 -ansi -fsanitize=address atoi.c -o atoi.exe
atoi
del *.exp *.lib *pdb *.exe