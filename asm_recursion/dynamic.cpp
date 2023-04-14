#include <bits/stdc++.h>

#define CACHE_LEN 2001

int DNUM_dynamic(int n, int *cache) {
  if (cache[n] != -1) {
    return cache[n];
  }
  if (cache[n - 2] == -1) {
    cache[n - 2] = DNUM_dynamic(n - 2, cache);
  }
  if (cache[n - 1] == -1) {
    cache[n - 1] = DNUM_dynamic(n - 1, cache);
  }
  // assert(cache[n - 2] != -1);
  // assert(cache[n - 1] != -1);
  // assert(cache[cache[n - 1]] != -1);
  // assert(cache[n - 1 - cache[n - 2]] != -1);
  return cache[cache[n - 1]] + cache[n - 1 - cache[n - 2]];
}

int main() {
  int cache[CACHE_LEN];
  for (int i = 0; i < CACHE_LEN; i++) {
    cache[i] = -1;
  }
  cache[0] = 0;
  cache[1] = 1;
  cache[2] = 1;
  int inp = 2000;
  for (int i = inp; i >= 0; i--) {
    std::cout << "DNUM(" << i << ") = " << DNUM_dynamic(i, cache) << "\n";
  }

  // for (int i = 0; i < inp; i++)
  // {
  //     std::cout << "DNUM(" << i << ") = " << DNUM_dynamic(i, cache) << "\n";
  // }

  // std::cout << "DNUM(" << inp << ") = " << DNUM_dynamic(inp, cache) << "\n";
  // for (int i = 0; i < CACHE_LEN; i++)
  // {
  //     std::cout << cache[i] << " ";
  // }
  std::cout << "\n";
  return 0;
}
