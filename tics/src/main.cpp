#include <iostream>

enum Res { O = 'O', X = 'X', Draw, Cont };

template <size_t size>
void printBoard(char b[][size]) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) std::cout << b[i][j] << " ";
    std::cout << "\n";
  }
}

template <size_t size>
void setPos(char b[][size], char curPl) {
  std::cout << curPl << "'s turn: ";
  int x, y;
  std::cin >> x >> y;
  while (x < 0 || x >= size || y < 0 || y >= size || b[x][y] != ' ') {
    std::cout << "Try again: ";
    std::cin >> x >> y;
  }
  b[x][y] = curPl;
}

template <size_t size>
bool isFull(char b[][size]) {
  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
      if (b[i][j] == ' ') return false;
  return true;
}

template <size_t size>
int check(char b[][size]) {
  bool ends = false;
  char first;
  for (int j = 0; j < size && !ends; ++j) {
    first = b[0][j];
    ends = true;
    for (int i = 0; i < size; ++i)
      if (b[i][j] != first || b[i][j] == ' ') ends = false;
  }
  if (ends) return first;
  for (int i = 0; i < size && !ends; ++i) {
    first = b[i][0];
    ends = true;
    for (int j = 0; j < size; ++j)
      if (b[i][j] != first || b[i][j] == ' ') ends = false;
  }
  if (ends) return first;
  if (b[1][1] != ' ') {
    if (b[0][0] == b[1][1] && b[0][0] == b[2][2]) return b[0][0];
    if (b[0][2] == b[1][1] && b[0][2] == b[2][0]) return b[0][2];
  }
  return Res::Cont;
}

void play() {
  int res = Res::Cont;
  char b[3][3], curPl = 'X';
  std::fill_n(&b[0][0], 9, ' ');
  do {
    setPos(b, curPl);
    curPl = curPl == 'X' ? 'O' : 'X';
    printBoard(b);
    res = check(b);
    if (res == Res::Cont && isFull(b)) {
      res = Res::Draw;
    }
  } while (res == Res::Cont);
  if (res == 'O' || res == 'X')
    std::cout << "\n" << (char)res << " wins\n";
  else
    std::cout << "\nDraw\n";
}

int main() {
  char cont = 'y';
  play();
  std::cout << "Play again? ";
  std::cin >> cont;
  while (cont == 'y') {
    play();
    std::cout << "Play again? ";
    std::cin >> cont;
  }
}
