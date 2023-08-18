all:
	clang++ -g -O2 -Weverything -std=c++20 -fsanitize=address -Wno-c++98-compat-pedantic Main.cpp Test.cpp -o main
run: all
	./main
format:
	clang-format -i -style=Google *.cpp
clean:
	rm main *perf*