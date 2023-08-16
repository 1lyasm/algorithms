all:
	clang++ -O2 -Weverything -std=c++20 -fsanitize=address -Wno-c++98-compat-pedantic main.cpp -o main
run: all
	./main
format:
	clang-format -i -style=Google main.cpp
clean:
	rm main