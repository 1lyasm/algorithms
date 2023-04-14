#include <iostream>

int DNUM(int n) {
  if (n == 0) {
    return 0;
  }
  if (n < 3) {
    return 1;
  } else if (n >= 3) {
    return DNUM(DNUM(n - 1)) + DNUM(n - 1 - DNUM(n - 2));
  }
}

int main() {
  for (int i = 0; i <= 35; i++) {
    std::cout << "DNUM(" << i << ") = " << DNUM(i) << "\n";
  }
  return 0;
}
