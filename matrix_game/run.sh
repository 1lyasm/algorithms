clang -ansi -O2 -Weverything -fsanitize=address *.c -o a.bin
./a.bin
rm *.bin