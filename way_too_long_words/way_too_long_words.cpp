#include <bits/stdc++.h>
#include <cassert>
#include <regex>

std::vector<std::string> sep_str(std::string s);
std::vector<int> vec_stoi(std::vector<std::string> vec);
int sum_vec(std::vector<int> v);

template <typename T> void print_vec(T val);

std::vector<int> comp_hours(int d, int S, std::vector<int> m,
                            std::vector<int> M);

int main() {

  std::string w_cnt_str;
  std::getline(std::cin, w_cnt_str);
  int w_cnt = std::stoi(w_cnt_str);

  std::vector<std::string> inp_vec;
  std::string word;

  for (int i = 0; i <= w_cnt - 1; i++) {
    std::getline(std::cin, word);
    inp_vec.push_back(word);
  }

  for (int i = 0; i <= inp_vec.size() - 1; i++) {
    if (inp_vec[i].size() > 10) {
      std::cout << inp_vec[i][0] << inp_vec[i].size() - 2
                << inp_vec[i][inp_vec[i].size() - 1];
    } else {
      std::cout << inp_vec[i];
    }
    if (i != inp_vec.size() - 1) {
      std::cout << "\n";
    }
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

template <typename T> void print_vec(T val) {
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
