all:
	clang++ src/main.cpp -O2 -Wall -Werror -fsanitize=address -o src/main
format:	
	clang-format -i -style=Google src/main.cpp
clean:
	rm src/main
