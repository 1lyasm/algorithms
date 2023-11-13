class Solution {
public:
    void printStrings(string &s1, string &s2) {
        std::cout << "s1: " << s1 << ", s2: " << s2 << "\n";
    }

    vector<int> makeVec(string &s) {
        vector<int> d;
        d.reserve(s.size());
        for (int i = 0; i < s.size(); ++i) {
            d.push_back(s[i]);
        }
        return d;
    }

    multiset<int> makeSet(string &s) {
        multiset<int> set_;
        for (int i = 0; i < s.size(); ++i) {
            set_.insert(s[i]);
        }
        return set_;
    }

    bool checkIfCanBreak(string s1, string s2) {
        bool res = false;
        int dir = -1;
        auto s1_s = makeSet(s1);
        auto s2_s = makeSet(s2);
        auto m1 = std::min_element(s1_s.begin(), s1_s.end());
        auto m2 = std::min_element(s2_s.begin(), s2_s.end());
        auto m1Val = *m1;
        auto m2Val = *m2;
        int curSize = s1_s.size();
        if (m1Val > m2Val) {
            dir = 0;
        } else if (m1Val < m2Val) {
            dir = 1;
        }
        do {
            m1 = std::min_element(s1_s.begin(), s1_s.end());
            m2 = std::min_element(s2_s.begin(), s2_s.end());
            m1Val = *m1;
            m2Val = *m2;
            if (dir == -1) {
                if (m1Val > m2Val) {
                    dir = 0;
                } else if (m1Val < m2Val) {
                    dir = 1;
                }
            } else if (dir && m1Val > m2Val ||
                !dir && m1Val < m2Val) {
                return false;
            }
            s1_s.erase(m1);
            s2_s.erase(m2);
            if (s1_s.size() == 0) {
                return true;
            }
        } while(1);
        return res;
    }
};

