class Solution {
 public:
  int minCost(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> costs(n + 1, INT_MAX / 2);
    costs[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
      int len = 0;
      vector<int> counts(n);
      for (int j = i; j < n; ++j) {
        if (++counts[nums[j]] == 2)
          len += 2;
        else if (counts[nums[j]] > 2)
          ++len;
        costs[i] = min(costs[i], len + k + costs[j + 1]);
      }
    }
    return costs[0];
  }
};
