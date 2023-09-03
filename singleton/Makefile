all:
	clang -O2 -Wall -Werror -Wpedantic -fsanitize=address src/singleton.c -o bin/singleton
format:
	clang-format -i -style="{BasedOnStyle: google, IndentWidth: 4}" src/*.c
