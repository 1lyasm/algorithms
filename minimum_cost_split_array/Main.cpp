class Solution {
public:
    int compVal(vector<int> &nums, int start, int end, int k) {
        int uniqueCnt = 0;
        for (int i = start; i <= end; ++i) {
            bool isUnique = true;
            for (int j = start; j <= end; ++j) {
                if (nums[i] == nums[j] && i != j) {
                    isUnique = false;
                    break;
                }
            }
            if (isUnique) {
                ++uniqueCnt;
            }
        }
        return end - start - uniqueCnt + k;
    }

    int solve(vector<int> &nums, int start, int end, int k) {
        if (end < start) {
            return 0;
        }
        if (end == start) {
            return k;
        }
        std::cout << "solve: start: " << start << ", end: " << end << "\n";
        int min = INT_MAX;
        for (int i = start; i < end; ++i) {
            int cost = solve(nums, start, i, k) + 
                solve(nums, i + 1, end, k);
            cost += compVal(nums, start, i, k) + 
                compVal(nums, i + 1, end, k);
            if (cost < min) {
                min = cost;
            }
        }
        return min;
    }

    int minCost(vector<int>& nums, int k) {
        return solve(nums, 0, nums.size() - 1, k);   
    }
};
