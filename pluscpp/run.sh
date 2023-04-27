clang++ -O2 -std=c++2b -Weverything \
    -Wno-c++98-compat \
    -fsanitize=address *.cpp -o pluscpp.exe
./pluscpp.exe
rm *.exe
