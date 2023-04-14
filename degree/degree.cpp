#include <bits/stdc++.h>

std::unordered_map<int, int>
comp_degs(std::vector<std::pair<int, int>> vrtx_pairs) {
  std::unordered_map<int, int> vrtx_deg_map;
  int vrtx_1, vrtx_2;
  for (long long unsigned int i = 0; i < vrtx_pairs.size(); i++) {
    vrtx_1 = vrtx_pairs[i].first;
    vrtx_2 = vrtx_pairs[i].second;
    if (!(vrtx_deg_map.contains(vrtx_1))) {
      vrtx_deg_map.insert({vrtx_1, 0});
    }
    if (!(vrtx_deg_map.contains(vrtx_2))) {
      vrtx_deg_map.insert({vrtx_2, 0});
    }
    vrtx_deg_map.at(vrtx_1)++;
    vrtx_deg_map.at(vrtx_2)++;
  }
  return vrtx_deg_map;
}

std::unordered_map<int, std::pair<int, int>>
comp_in_out_degs(std::vector<std::pair<int, int>> vrtx_pairs) {
  std::unordered_map<int, std::pair<int, int>> vrtx_deg_map;
  int vrtx_1, vrtx_2;
  for (long long unsigned int i = 0; i < vrtx_pairs.size(); i++) {
    vrtx_1 = vrtx_pairs[i].first;
    vrtx_2 = vrtx_pairs[i].second;
    if (!(vrtx_deg_map.contains(vrtx_1))) {
      vrtx_deg_map.insert({vrtx_1, {0, 0}});
    }
    if (!(vrtx_deg_map.contains(vrtx_2))) {
      vrtx_deg_map.insert({vrtx_2, {0, 0}});
    }
    vrtx_deg_map.at(vrtx_1).first++;
    vrtx_deg_map.at(vrtx_2).second++;
  }
  return vrtx_deg_map;
}

int main() {
  std::vector<std::pair<int, int>> vrtx_pairs = {{1, 3}, {1, 2}, {2, 3},
                                                 {2, 4}, {3, 4}, {4, 5}};
  std::unordered_map<int, int> degs = comp_degs(vrtx_pairs);

  int deg;
  for (auto vrtx_deg : degs) {
    deg = vrtx_deg.second;
    std::cout << "\nVertex label: " << vrtx_deg.first
              << "\nVertex degree: " << deg << "\n";
    switch (vrtx_deg.first) {
    case 1:
      assert(deg == 2);
      break;
    case 2:
      assert(deg == 3);
      break;
    case 3:
      assert(deg == 3);
      break;
    case 4:
      assert(deg == 3);
      break;
    case 5:
      assert(deg == 1);
      break;
    }
  }

  std::vector<std::pair<int, int>> vrtx_pairs_ordered = {
      {1, 3}, {1, 2}, {2, 3}, {2, 4}, {3, 4}, {4, 5}};
  std::unordered_map<int, std::pair<int, int>> in_out_degs =
      comp_in_out_degs(vrtx_pairs_ordered);

  int out_deg, in_deg;
  for (auto vrtx_deg : in_out_degs) {
    out_deg = vrtx_deg.second.first;
    in_deg = vrtx_deg.second.second;
    std::cout << "\nVertex label: " << vrtx_deg.first
              << "\nVertex out degree: " << out_deg
              << "\nVertex in degree: " << in_deg << "\n";
    switch (vrtx_deg.first) {
    case 1:
      assert(out_deg == 2);
      assert(in_deg == 0);
      break;
    case 2:
      assert(out_deg == 2);
      assert(in_deg == 1);
      break;
    case 3:
      assert(out_deg == 1);
      assert(in_deg == 2);
      break;
    case 4:
      assert(out_deg == 1);
      assert(in_deg == 2);
      break;
    case 5:
      assert(out_deg == 0);
      assert(in_deg == 1);
      break;
    }
  }

  std::cout << "\n";
  return 0;
}
