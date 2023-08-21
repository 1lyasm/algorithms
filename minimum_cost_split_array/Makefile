all:
	clang++ -g -O2 -Weverything -std=c++20 -fsanitize=address -Wno-c++98-compat-pedantic Main.cpp Test.cpp -o main
run:
	./main
format:
	clang-format -i -style=Google *.cpp
profile: all
	perf record -g ./main --benchmark
	perf report -g
clean:
	rm main *perf*