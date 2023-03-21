cls
clang -O2 -fsanitize=address -march=alderlake Source/Main.c -o Binary/Main.c.bin
cd Binary
Main.c.bin
cd ..