clang++ -c -O2 -std=c++2b -Weverything ^
    -fsanitize=address *.cpp
del *.exp *.lib *.pdb *.o
