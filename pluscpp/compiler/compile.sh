mkdir ../build

mkdir ../build/compiler

mkdir ../build/compiler/Lex

clang++ -c -O2 -std=c++2b \
  -Weverything -Wno-c++98-compat -Wno-padded\
  -fsanitize=address \
  lib/Lex/Token.cpp  \
  -Iinclude \
  -o ../build/compiler/Lex/Token.cpp.o

clang++ -c -O2 -std=c++2b \
  -Weverything -Wno-c++98-compat -Wno-padded\
  -fsanitize=address \
  lib/Lex/Lex.cpp  \
  -Iinclude \
  -o ../build/compiler/Lex/Lex.cpp.o


mkdir ../build/compiler/Diagnostic/

clang++ -c -O2 -std=c++2b \
  -Weverything -Wno-c++98-compat -Wno-padded\
  -fsanitize=address \
  lib/Diagnostic/Diagnostic.cpp  \
  -Iinclude \
  -o ../build/compiler/Diagnostic/Diagnostic.cpp.o

mkdir ../build/compiler/Option/

clang++ -c -O2 -std=c++2b \
  -Weverything -Wno-c++98-compat -Wno-padded\
  -fsanitize=address \
  lib/Option/ArgVerifier.cpp  \
  -Iinclude \
  -o ../build/compiler/Option/ArgVerifier.cpp.o

clang++ -c -O2 -std=c++2b \
  -Weverything -Wno-c++98-compat -Wno-padded\
  -fsanitize=address \
  lib/Option/Option.cpp  \
  -Iinclude \
  -o ../build/compiler/Option/Option.cpp.o

mkdir ../build/compiler/Driver/

clang++ -c -O2 -std=c++2b \
  -Weverything -Wno-c++98-compat -Wno-padded\
  -fsanitize=address \
  lib/Driver/Driver.cpp  \
  -Iinclude \
  -o ../build/compiler/Driver/Driver.cpp.o

mkdir ../build/bin/
clang++ -fsanitize=address \
  ../build/compiler/Lex/*.o ../build/compiler/Driver/*.o \
  ../build/compiler/Option/*.o ../build/compiler/Diagnostic/*.o \
  -o ../build/bin/compiler
