class Solution {
 public:
  int minCost(vector<int>& nums, int k) {
    const int nMax = 1001, n = nums.size();
    array<int, nMax> costs, counts;
    costs.fill(INT_MAX / 2);
    costs[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
      int len = 0;
      counts.fill(0);
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
