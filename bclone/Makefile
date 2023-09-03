all:
	clang -O2 -Wall -Werror -Wpedantic -fsanitize=address src/bclone.c -o bin/bclone
format:
	clang-format -i -style="{BasedOnStyle: google, IndentWidth: 4}" src/*.c
