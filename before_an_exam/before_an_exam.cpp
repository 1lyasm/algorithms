#include <bits/stdc++.h>

#include <cassert>
#include <regex>

std::vector<std::string> sep_str(std::string s);
std::vector<int> vec_stoi(std::vector<std::string> vec);
int sum_vec(std::vector<int> v);

template <typename T>
void print_vec(T val);

std::vector<int> comp_hours(int d, int S, std::vector<int> m,
                            std::vector<int> M);

int main() {
  std::string line1;
  std::getline(std::cin, line1);

  std::vector<std::string> vec1 = sep_str(line1);

  std::vector<int> vec1_int = vec_stoi(vec1);
  int d = vec1_int[0];
  int S = vec1_int[1];

  std::vector<int> m, M;
  std::string line;
  std::vector<std::string> line_sep;
  std::vector<int> line_int;
  for (int i = 0; i <= d - 1; i++) {
    std::getline(std::cin, line);
    line_sep = sep_str(line);
    line_int = vec_stoi(line_sep);
    m.push_back(line_int[0]);
    M.push_back(line_int[1]);
  }

  int s_m = sum_vec(m), s_M = sum_vec(M);

  bool in_range = ((s_m <= S) && (S <= s_M));
  if (in_range) {
    std::cout << "YES\n";
    print_vec(comp_hours(d, S, m, M));
  } else {
    std::cout << "NO";
  }

  return 0;
}

std::vector<std::string> sep_str(std::string s) {
  std::vector<std::string> vec;
  int i = 0;
  while (s[i] != ' ') {
    i++;
  }
  vec.push_back(s.substr(0, i));
  vec.push_back(s.substr(i + 1, vec.size() - 1 - i));
  return vec;
}

std::vector<int> vec_stoi(std::vector<std::string> vec) {
  std::vector<int> vec_int;
  for (auto x : vec) {
    vec_int.push_back(std::stoi(x));
  }
  return vec_int;
}

template <typename T>
void print_vec(T val) {
  for (int i = 0; i <= val.size() - 1; i++) {
    std::cout << val[i];
    if (i != val.size() - 1) {
      std::cout << ' ';
    }
  }
  return;
}

std::vector<int> comp_hours(int d, int S, std::vector<int> m,
                            std::vector<int> M) {
  std::vector<int> t;
  for (int i = 0; i <= m.size() - 1; i++) {
    t.push_back((int)((m[i] + M[i]) / 2));
  }

  int s_t = sum_vec(t);

  int del = S - s_t;

  int is_above;
  if (del > 0) {
    is_above = 1;
  } else if (del < 0) {
    is_above = -1;
  } else {
    is_above = 0;
  }

  del = (int)(abs(del));
  int i = 0;
  for (int j = 0; j <= del - 1; j++) {
    while (((m[i] == t[i]) && (is_above < 0)) ||
           ((t[i] == M[i]) && (is_above > 0))) {
      i++;
    }
    t[i] += is_above;
  }
  return t;
  assert(sum_vec(t) == S);
}

int sum_vec(std::vector<int> v) {
  int s = 0;
  for (auto x : v) {
    s += x;
  }
  return s;
}
