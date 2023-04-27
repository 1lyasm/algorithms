clang++-15 -O2 -std=c++2b -Weverything \
    -Wno-c++98-compat \
    -fsanitize=address -fprebuilt-module-path=. file_reader.cppm --precompile -o file_reader.pcm
clang++-15 -O2 -std=c++2b -Weverything \
    -Wno-c++98-compat \
    -fsanitize=address -fprebuilt-module-path=. source.cppm --precompile -o source.pcm
clang++-15 -O2 -std=c++2b main.cpp -Weverything \
    -Wno-c++98-compat \
    -fsanitize=address \
    -fprebuilt-module-path=. source.pcm file_reader.pcm \
    -o pluscpp.out
./pluscpp.out
rm *.out *.pcm
