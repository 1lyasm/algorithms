class Solution {
public:
  bool checkIfCanBreak(string s1, string s2) {
    bool res = false;
    int dir = -1;
    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    if (s1[0] > s2[0]) {
      dir = 0;
    } else if (s1[0] < s2[0]) {
      dir = 1;
    }
    for (int i = 0; i < s1.size(); ++i) {
      if (dir == -1) {
        if (s1[i] > s2[i]) {
          dir = 0;
        } else if (s1[i] < s2[i]) {
          dir = 1;
        }
      } else if (dir && s1[i] > s2[i] || !dir && s1[i] < s2[i]) {
        return false;
      }
    }
    return true;
  }
};

