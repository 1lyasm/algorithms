clang++ -c -O2 -std=c++2b -Weverything ^
    -Wno-c++98-compat ^
    -fsanitize=address *.cpp
del *.exp *.lib *.pdb *.o
