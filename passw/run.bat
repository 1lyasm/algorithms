clang -ansi -fsanitize=address passw.c -o passw.exe
passw
del passw.exp passw.lib passw.pdb passw.exe
