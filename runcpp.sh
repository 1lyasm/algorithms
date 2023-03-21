clang++ -O2 -std=c++17 -fsanitize=leak Source/Main.cpp -o ./Binary/Main.cpp.bin -lm
ASAN_OPTIONS=detect_leaks=1 ./Binary/Main.cpp.bin