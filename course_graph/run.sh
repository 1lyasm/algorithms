clang -g -ansi -O2 -Wall -fsanitize=address main.c -o a.bin
./a.bin
rm a.bin
