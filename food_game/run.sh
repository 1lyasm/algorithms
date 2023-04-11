clang -O2 -Weverything -Werror \
    -fsanitize=address -ansi \
    food_game.c -o food_game
./food_game