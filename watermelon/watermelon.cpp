#include <bits/stdc++.h>

using namespace std;

int main() {
  string weight_str;
  cin >> weight_str;

  int weight = std::stoi(weight_str);
  if ((weight % 2 == 0) && (weight > 2)) {
    cout << "YES";
  } else {
    cout << "NO";
  }

  return 0;
}
