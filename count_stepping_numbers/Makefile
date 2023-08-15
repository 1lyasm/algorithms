all:
	clang++ -O0 -Weverything -std=c++20 -fsanitize=address main.cpp -o main
run: main
	./main
clean:
	rm main