all:
	clang++ -O0 -Weverything -std=c++20 -fsanitize=address main.cpp -o main
run: main
	./main
format:
	clang-format -i -style=Google main.cpp
clean:
	rm main