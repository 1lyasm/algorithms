#include <bits/stdc++.h>
using namespace std;

#define rep(i, s, e) for (int i = s; i <= e; i++)

template <typename T> constexpr T myConv(T x, int n, T y, int m){
    T w, t, s; pair<double, double> rw{}, rt{};
    if (n > m){w = x; t = y;} else {w = y; t = x;}
    rep(i, 0, (n + m - 2)){
        auto inv_dot(0.0);
        rep(j, 0, (rw.second - rw.first)) {inv_dot += w[rw.first + j] * t[rt.first - j];}
        s.push_back(inv_dot);
        if (i <= m - 2){ rw.second++; rt.first++;}
        else if (i <= n - 1) {rw.first++; rw.second++;} 
        else {rw.first++; rt.second++;}
    }
    return s;
}

int main(){
    const deque<double> x = {1, 2, 3}, y = {0, 1, 0.5};
    const auto n(3), m(3); const auto s = myConv(x, n, y, m);
    for (auto i: s){cout << i << " ";}
    return 0;
}

