#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

template <typename T>
void print(const T &val) {
  for (const auto &x : val) std::cout << x << '\n';
  std::cout << '\n';
}

void initializeGarden(int arr[][10], int nRow) {
  srand((unsigned short)time(NULL));
  for (int row = 0; row < nRow; row++) {
    for (int col = 0; col < 10; col++) arr[row][col] = rand() % 4;
  }
}

void print2D(const int arr[][10], int row) {
  for (int i = 0; i < row; i++) {
    for (int col = 0; col < 10; col++) {
      if (arr[i][col] == 0)
        std::cout << ' ';
      else if (arr[i][col] == 1)
        std::cout << '.';
      else if (arr[i][col] == 2)
        std::cout << 'O';
      else if (arr[i][col] == 3)
        std::cout << 'X';
      std::cout << ' ';
    }
    std::cout << '\n';
  }
}

void randomize(int arr[]) {
  int rowChange = rand() % 3 - 1;
  int colChange = rand() % 3 - 1;
  while (rowChange == 0 && colChange == 0) {
    rowChange = rand() % 3 - 1;
    colChange = rand() % 3 - 1;
  }
  arr[0] = rowChange;
  arr[1] = colChange;
}

void dropSeedToNeighbour(int arr[][10], int nRow, bool changedArr[][10]) {
  int dirChange[2] = {0, 0};
  for (int row = 0; row < nRow; row++) {
    for (int col = 0; col < 10; col++) {
      if (arr[row][col] == 2) {
        randomize(dirChange);
        if ((row + dirChange[0] < nRow) && (col + dirChange[1] < 10) &&
            arr[row + dirChange[0]][col + dirChange[1]] == 0) {
          arr[row + dirChange[0]][col + dirChange[1]] = 1;
          changedArr[row + dirChange[0]][col + dirChange[1]] = true;
        }
      }
    }
  }
}

void timeStep(int arr[][10], int nRow) {
  bool changedArr[5][10] = {
      {false, false, false, false, false, false, false, false, false, false},
      {false, false, false, false, false, false, false, false, false, false},
      {false, false, false, false, false, false, false, false, false, false},
      {false, false, false, false, false, false, false, false, false, false},
      {false, false, false, false, false, false, false, false, false, false}};
  dropSeedToNeighbour(arr, nRow, changedArr);
  for (int row = 0; row < nRow; row++) {
    for (int col = 0; col < 10; col++) {
      if (arr[row][col] > 0 && changedArr[row][col] == false) {
        arr[row][col]++;
        if (arr[row][col] > 3) arr[row][col] = 0;
      }
    }
  }
}

int main() {
  std::cout << "\nQuestion 6\n";
  const int ROW(5), COL(10);
  int garden[ROW][COL];
  initializeGarden(garden, ROW);
  std::cout << "\nGarden: \n";
  print2D(garden, ROW);
  std::string response = "y";
  while (tolower(response[0]) == 'y') {
    timeStep(garden, ROW);
    std::cout << "\nAfter time step: \n";
    print2D(garden, ROW);
    std::cout << "\nContinue('y' for yes)? ";
    std::cin >> response;
  }
  return 0;
}
