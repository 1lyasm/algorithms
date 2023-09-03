clang -O0 -Weverything -ansi \
    -fsanitize=address \
    src/main.c -o src/main
ASAN_OPTIONS=detect_leaks=1 ./src/main
rm src/main