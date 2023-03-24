import sys, os

os.system('cmake -GNinja -S . -B build -DCMAKE_C_COMPILER="clang" -DCMAKE_CXX_COMPILER="clang++"')
