clang++ -O2 Source/Main.cpp -o ./Binary/Main.cpp.bin
clang++ -O2 -S Source/Main.cpp -o Binary/Main.cpp.asm
cd Binary
Main.cpp.bin
cd ..