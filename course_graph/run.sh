clang -g -ansi -O0 -Wall -fsanitize=address main.c -o a.bin
./a.bin
rm a.bin