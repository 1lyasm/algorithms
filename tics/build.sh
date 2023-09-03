#!/usr/bin/bash
clang++ src/main.cpp -O2 -Wall -Werror -fsanitize=address -o src/main

